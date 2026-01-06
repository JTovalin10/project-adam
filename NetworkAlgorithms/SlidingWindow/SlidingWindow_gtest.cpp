#include <chrono>
#include <thread>

#include "gtest/gtest.h"
#include "sliding_window.h"

using namespace network;

// ============================================================================
// Packet Tests
// ============================================================================

class PacketTest : public ::testing::Test {
 protected:
  void SetUp() override {}
};

TEST_F(PacketTest, ConstructorInitializesCorrectly) {
  std::vector<uint8_t> data = {0xAA, 0xBB, 0xCC};
  Packet packet(5, data);

  EXPECT_EQ(packet.seq_num, 5);
  EXPECT_EQ(packet.data.size(), 3);
  EXPECT_EQ(packet.data[0], 0xAA);
  EXPECT_EQ(packet.data[1], 0xBB);
  EXPECT_EQ(packet.data[2], 0xCC);
}

TEST_F(PacketTest, EqualityOperatorWorks) {
  std::vector<uint8_t> data1 = {0xAA, 0xBB};
  std::vector<uint8_t> data2 = {0xAA, 0xBB};
  std::vector<uint8_t> data3 = {0xCC, 0xDD};

  Packet packet1(1, data1);
  Packet packet2(1, data2);
  Packet packet3(2, data3);

  EXPECT_TRUE(packet1 == packet2);
  EXPECT_FALSE(packet1 == packet3);
}

// ============================================================================
// GBN Sender Tests
// ============================================================================

class GBNSenderTest : public ::testing::Test {
 protected:
  void SetUp() override { sender_ = new GBNSender(4, 500); }

  void TearDown() override { delete sender_; }

  GBNSender* sender_;
};

TEST_F(GBNSenderTest, InitialStateIsCorrect) {
  EXPECT_EQ(sender_->GetBase(), 0);
  EXPECT_EQ(sender_->GetNextSeqNum(), 0);
  EXPECT_EQ(sender_->GetWindowUsage(), 0);
  EXPECT_FALSE(sender_->IsWindowFull());
}

TEST_F(GBNSenderTest, SendIncrementsSeqNum) {
  std::vector<uint8_t> data = {0xAA, 0xBB};
  sender_->Send(data);

  EXPECT_EQ(sender_->GetNextSeqNum(), 1);
  EXPECT_EQ(sender_->GetWindowUsage(), 1);
  EXPECT_FALSE(sender_->IsWindowFull());
}

TEST_F(GBNSenderTest, SendMultiplePackets) {
  for (int i = 0; i < 3; i++) {
    std::vector<uint8_t> data = {static_cast<uint8_t>(i)};
    sender_->Send(data);
  }

  EXPECT_EQ(sender_->GetNextSeqNum(), 3);
  EXPECT_EQ(sender_->GetWindowUsage(), 3);
  EXPECT_FALSE(sender_->IsWindowFull());
}

TEST_F(GBNSenderTest, WindowFillsCorrectly) {
  for (int i = 0; i < 4; i++) {
    std::vector<uint8_t> data = {static_cast<uint8_t>(i)};
    sender_->Send(data);
  }

  EXPECT_TRUE(sender_->IsWindowFull());
  EXPECT_EQ(sender_->GetWindowUsage(), 4);
}

TEST_F(GBNSenderTest, ProcessAckSlidesWindow) {
  for (int i = 0; i < 3; i++) {
    sender_->Send({static_cast<uint8_t>(i)});
  }

  sender_->ProcessAck(0);

  EXPECT_EQ(sender_->GetBase(), 1);
  EXPECT_EQ(sender_->GetWindowUsage(), 2);
  EXPECT_FALSE(sender_->IsWindowFull());
}

TEST_F(GBNSenderTest, CumulativeAckRemovesMultiplePackets) {
  for (int i = 0; i < 4; i++) {
    sender_->Send({static_cast<uint8_t>(i)});
  }

  sender_->ProcessAck(2);

  EXPECT_EQ(sender_->GetBase(), 3);
  EXPECT_EQ(sender_->GetWindowUsage(), 1);
  EXPECT_FALSE(sender_->IsWindowFull());
}

TEST_F(GBNSenderTest, OldAckIsIgnored) {
  for (int i = 0; i < 4; i++) {
    sender_->Send({static_cast<uint8_t>(i)});
  }

  sender_->ProcessAck(2);
  uint32_t base_before = sender_->GetBase();

  sender_->ProcessAck(1);

  EXPECT_EQ(sender_->GetBase(), base_before);
}

TEST_F(GBNSenderTest, NoTimeoutBeforeDeadline) {
  sender_->Send({0xAA});

  auto retransmit = sender_->CheckTimeouts();
  EXPECT_TRUE(retransmit.empty());
}

TEST_F(GBNSenderTest, TimeoutTriggersRetransmission) {
  GBNSender sender(4, 100);

  sender.Send({0xAA});
  sender.Send({0xBB});

  std::this_thread::sleep_for(std::chrono::milliseconds(150));

  auto retransmit = sender.CheckTimeouts();

  EXPECT_EQ(retransmit.size(), 2);
  EXPECT_EQ(retransmit[0].seq_num, 0);
  EXPECT_EQ(retransmit[1].seq_num, 1);
}

TEST_F(GBNSenderTest, TimeoutRetransmitsAllPackets) {
  GBNSender sender(4, 100);

  for (int i = 0; i < 4; i++) {
    sender.Send({static_cast<uint8_t>(i)});
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(150));

  auto retransmit = sender.CheckTimeouts();
  EXPECT_EQ(retransmit.size(), 4);
}

TEST_F(GBNSenderTest, AckAfterTimeoutResetsTimer) {
  GBNSender sender(4, 100);

  sender.Send({0xAA});
  std::this_thread::sleep_for(std::chrono::milliseconds(150));

  auto retransmit1 = sender.CheckTimeouts();
  EXPECT_EQ(retransmit1.size(), 1);

  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  auto retransmit2 = sender.CheckTimeouts();
  EXPECT_TRUE(retransmit2.empty());
}

// ============================================================================
// GBN Receiver Tests
// ============================================================================

class GBNReceiverTest : public ::testing::Test {
 protected:
  void SetUp() override { receiver_ = new GBNReceiver(4); }

  void TearDown() override { delete receiver_; }

  GBNReceiver* receiver_;
};

TEST_F(GBNReceiverTest, InitialStateIsCorrect) {
  EXPECT_EQ(receiver_->GetExpectedSeqNum(), 0);
}

TEST_F(GBNReceiverTest, AcceptsInOrderPacket) {
  Packet packet(0, {0xAA});
  uint32_t ack = receiver_->ReceivePacket(packet);

  EXPECT_EQ(ack, 0);
  EXPECT_EQ(receiver_->GetExpectedSeqNum(), 1);
}

TEST_F(GBNReceiverTest, AcceptsMultipleInOrderPackets) {
  for (int i = 0; i < 3; i++) {
    Packet packet(i, {static_cast<uint8_t>(i)});
    uint32_t ack = receiver_->ReceivePacket(packet);
    EXPECT_EQ(ack, i);
  }

  EXPECT_EQ(receiver_->GetExpectedSeqNum(), 3);
}

TEST_F(GBNReceiverTest, DiscardsOutOfOrderPacket) {
  receiver_->ReceivePacket(Packet(0, {0xAA}));

  uint32_t ack = receiver_->ReceivePacket(Packet(2, {0xCC}));

  EXPECT_EQ(ack, 0);
  EXPECT_EQ(receiver_->GetExpectedSeqNum(), 1);
}

TEST_F(GBNReceiverTest, ReturnsLastGoodAckForOutOfOrder) {
  receiver_->ReceivePacket(Packet(0, {0xAA}));
  receiver_->ReceivePacket(Packet(1, {0xBB}));

  uint32_t ack = receiver_->ReceivePacket(Packet(5, {0xFF}));

  EXPECT_EQ(ack, 1);
}

TEST_F(GBNReceiverTest, GetNextPacketWorks) {
  receiver_->ReceivePacket(Packet(0, {0xAA}));

  auto packet = receiver_->GetNextPacket();
  ASSERT_TRUE(packet.has_value());
  EXPECT_EQ(packet->seq_num, 0);
  EXPECT_EQ(packet->data[0], 0xAA);
}

TEST_F(GBNReceiverTest, GetNextPacketReturnsNulloptWhenEmpty) {
  auto packet = receiver_->GetNextPacket();
  EXPECT_FALSE(packet.has_value());
}

TEST_F(GBNReceiverTest, GetNextPacketReturnsMultiple) {
  for (int i = 0; i < 3; i++) {
    receiver_->ReceivePacket(Packet(i, {static_cast<uint8_t>(i)}));
  }

  for (int i = 0; i < 3; i++) {
    auto packet = receiver_->GetNextPacket();
    ASSERT_TRUE(packet.has_value());
    EXPECT_EQ(packet->seq_num, i);
  }

  auto empty = receiver_->GetNextPacket();
  EXPECT_FALSE(empty.has_value());
}

TEST_F(GBNReceiverTest, EdgeCaseExpectedSeqNumZero) {
  Packet packet(5, {0xFF});
  uint32_t ack = receiver_->ReceivePacket(packet);

  EXPECT_EQ(ack, 0);
}

// ============================================================================
// GBN Integration Tests
// ============================================================================

class GBNIntegrationTest : public ::testing::Test {
 protected:
  void SetUp() override {
    sender_ = new GBNSender(4, 500);
    receiver_ = new GBNReceiver(4);
  }

  void TearDown() override {
    delete sender_;
    delete receiver_;
  }

  GBNSender* sender_;
  GBNReceiver* receiver_;
};

TEST_F(GBNIntegrationTest, BasicSendReceive) {
  sender_->Send({0xAA});

  Packet packet(0, {0xAA});
  uint32_t ack = receiver_->ReceivePacket(packet);
  sender_->ProcessAck(ack);

  EXPECT_EQ(sender_->GetBase(), 1);

  auto delivered = receiver_->GetNextPacket();
  ASSERT_TRUE(delivered.has_value());
  EXPECT_EQ(delivered->seq_num, 0);
}

TEST_F(GBNIntegrationTest, MultiplePacketsInOrder) {
  for (int i = 0; i < 5; i++) {
    sender_->Send({static_cast<uint8_t>(i)});

    Packet packet(i, {static_cast<uint8_t>(i)});
    uint32_t ack = receiver_->ReceivePacket(packet);
    sender_->ProcessAck(ack);
  }

  EXPECT_EQ(sender_->GetBase(), 5);

  for (int i = 0; i < 5; i++) {
    auto p = receiver_->GetNextPacket();
    ASSERT_TRUE(p.has_value());
    EXPECT_EQ(p->seq_num, i);
  }
}

TEST_F(GBNIntegrationTest, PacketLossScenario) {
  GBNSender sender(4, 100);
  GBNReceiver receiver(4);

  sender.Send({0xAA});
  sender.Send({0xBB});
  sender.Send({0xCC});

  receiver.ReceivePacket(Packet(0, {0xAA}));
  uint32_t ack2 = receiver.ReceivePacket(Packet(2, {0xCC}));

  EXPECT_EQ(ack2, 0);

  std::this_thread::sleep_for(std::chrono::milliseconds(150));

  auto retransmit = sender.CheckTimeouts();
  EXPECT_EQ(retransmit.size(), 3);

  for (auto& pkt : retransmit) {
    receiver.ReceivePacket(pkt);
  }

  for (int i = 0; i < 3; i++) {
    auto p = receiver.GetNextPacket();
    ASSERT_TRUE(p.has_value());
    EXPECT_EQ(p->seq_num, i);
  }
}

TEST_F(GBNIntegrationTest, WindowFlowControl) {
  for (int i = 0; i < 4; i++) {
    sender_->Send({static_cast<uint8_t>(i)});
  }

  EXPECT_TRUE(sender_->IsWindowFull());

  sender_->ProcessAck(0);

  EXPECT_FALSE(sender_->IsWindowFull());
  sender_->Send({0xFF});
  EXPECT_TRUE(sender_->IsWindowFull());
}

TEST_F(GBNIntegrationTest, DuplicateAck) {
  sender_->Send({0xAA});
  sender_->Send({0xBB});

  Packet packet(0, {0xAA});
  receiver_->ReceivePacket(packet);

  uint32_t ack1 = receiver_->ReceivePacket(packet);
  uint32_t ack2 = receiver_->ReceivePacket(packet);

  EXPECT_EQ(ack1, ack2);
}

// ============================================================================
// SR Sender Tests
// ============================================================================

class SRSenderTest : public ::testing::Test {
 protected:
  void SetUp() override { sender_ = new SRSender(4, 500); }

  void TearDown() override { delete sender_; }

  SRSender* sender_;
};

TEST_F(SRSenderTest, InitialStateIsCorrect) {
  EXPECT_EQ(sender_->GetBase(), 0);
  EXPECT_EQ(sender_->GetNextSeqNum(), 0);
}

TEST_F(SRSenderTest, SendIncrementsSeqNum) {
  sender_->Send({0xAA});
  EXPECT_EQ(sender_->GetNextSeqNum(), 1);
}

TEST_F(SRSenderTest, IndividualAckMarksPacket) {
  for (int i = 0; i < 3; i++) {
    sender_->Send({static_cast<uint8_t>(i)});
  }

  sender_->ProcessAck(2);

  EXPECT_EQ(sender_->GetBase(), 0);
}

TEST_F(SRSenderTest, WindowSlidesWhenBaseAcked) {
  for (int i = 0; i < 3; i++) {
    sender_->Send({static_cast<uint8_t>(i)});
  }

  sender_->ProcessAck(2);
  EXPECT_EQ(sender_->GetBase(), 0);

  sender_->ProcessAck(1);
  EXPECT_EQ(sender_->GetBase(), 0);

  sender_->ProcessAck(0);
  EXPECT_EQ(sender_->GetBase(), 3);
}

TEST_F(SRSenderTest, SelectiveRetransmission) {
  SRSender sender(4, 100);

  for (int i = 0; i < 3; i++) {
    sender.Send({static_cast<uint8_t>(i)});
  }

  sender.ProcessAck(0);
  sender.ProcessAck(2);

  std::this_thread::sleep_for(std::chrono::milliseconds(150));

  auto retransmit = sender.CheckTimeouts();
  EXPECT_EQ(retransmit.size(), 1);
  EXPECT_EQ(retransmit[0].seq_num, 1);
}

// ============================================================================
// SR Receiver Tests
// ============================================================================

class SRReceiverTest : public ::testing::Test {
 protected:
  void SetUp() override { receiver_ = new SRReceiver(4); }

  void TearDown() override { delete receiver_; }

  SRReceiver* receiver_;
};

TEST_F(SRReceiverTest, InitialStateIsCorrect) {
  EXPECT_EQ(receiver_->GetBase(), 0);
}

TEST_F(SRReceiverTest, BuffersOutOfOrderPackets) {
  receiver_->ReceivePacket(Packet(2, {0xCC}));
  EXPECT_EQ(receiver_->GetBase(), 0);

  receiver_->ReceivePacket(Packet(0, {0xAA}));
  EXPECT_EQ(receiver_->GetBase(), 1);

  receiver_->ReceivePacket(Packet(1, {0xBB}));
  EXPECT_EQ(receiver_->GetBase(), 3);
}

TEST_F(SRReceiverTest, GetNextPacketReturnsInOrder) {
  receiver_->ReceivePacket(Packet(2, {0xCC}));
  receiver_->ReceivePacket(Packet(0, {0xAA}));
  receiver_->ReceivePacket(Packet(1, {0xBB}));

  auto p0 = receiver_->GetNextPacket();
  ASSERT_TRUE(p0.has_value());
  EXPECT_EQ(p0->seq_num, 0);

  auto p1 = receiver_->GetNextPacket();
  ASSERT_TRUE(p1.has_value());
  EXPECT_EQ(p1->seq_num, 1);

  auto p2 = receiver_->GetNextPacket();
  ASSERT_TRUE(p2.has_value());
  EXPECT_EQ(p2->seq_num, 2);

  auto empty = receiver_->GetNextPacket();
  EXPECT_FALSE(empty.has_value());
}

TEST_F(SRReceiverTest, DuplicatePacketReturnsAck) {
  receiver_->ReceivePacket(Packet(0, {0xAA}));
  receiver_->ReceivePacket(Packet(1, {0xBB}));

  uint32_t ack = receiver_->ReceivePacket(Packet(0, {0xAA}));
  EXPECT_EQ(ack, 0);
}

TEST_F(SRReceiverTest, PacketBeyondWindow) {
  uint32_t ack = receiver_->ReceivePacket(Packet(10, {0xFF}));
  EXPECT_EQ(ack, 0);
}

// ============================================================================
// SR Integration Tests
// ============================================================================

class SRIntegrationTest : public ::testing::Test {
 protected:
  void SetUp() override {
    sender_ = new SRSender(4, 500);
    receiver_ = new SRReceiver(4);
  }

  void TearDown() override {
    delete sender_;
    delete receiver_;
  }

  SRSender* sender_;
  SRReceiver* receiver_;
};

TEST_F(SRIntegrationTest, OutOfOrderDelivery) {
  for (int i = 0; i < 4; i++) {
    sender_->Send({static_cast<uint8_t>(i)});
  }

  uint32_t ack2 = receiver_->ReceivePacket(Packet(2, {0xCC}));
  sender_->ProcessAck(ack2);

  uint32_t ack0 = receiver_->ReceivePacket(Packet(0, {0xAA}));
  sender_->ProcessAck(ack0);

  uint32_t ack3 = receiver_->ReceivePacket(Packet(3, {0xDD}));
  sender_->ProcessAck(ack3);

  uint32_t ack1 = receiver_->ReceivePacket(Packet(1, {0xBB}));
  sender_->ProcessAck(ack1);

  EXPECT_EQ(sender_->GetBase(), 4);

  for (int i = 0; i < 4; i++) {
    auto p = receiver_->GetNextPacket();
    ASSERT_TRUE(p.has_value());
    EXPECT_EQ(p->seq_num, i);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
