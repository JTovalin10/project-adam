#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstddef>        // for std::size_t
#include <stdexcept>      // for std::out_of_range (throws)

/**
 * A dynamic array template that stores elements of type T
 * 
 * This vector is suppose to mimic std::Vector
 * 
 * @tparam T the type of elements stored in the vector
 */

template<typename T> 
class Vector {
    public:
    // ---- Type Aliases ---- //

    // The standarize types for compatibility with STL algorithms
    using size_type = std::size_t;
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;

    // ---- Constructors & DESTRUCTOR ---- //

    /**
     * Creates an empty vector with a default inital capacity
     */
    Vector();

    /**
     * Constructs a vector by coping the contents of another vector
     * 
     * ARGS:
     * other: the Vector whose content will be copied
     */
    Vector(const Vector& other);

    /**
     * Destroys the vector and safely deallocates the dynamically allocated memory.
     */
    ~Vector();

    /**
     * Performs a deep copy of another Vector's content
     * 
     * ARGS:
     * other: The Vector whose content will be copied
     * 
     * RETURNS:
     * A reference to the current Vector (*this)
     */
    Vector& operator=(const Vector& other);

    // ---- Element Access ---- //

    /**
     * Returns a mutable reference to the element at the given index
     * 
     * REQUIRES:
     * index is a valid position (0 <= index < size_)
     * 
     * ARGS:
     * index: The position of the element
     * 
     * RETURNS:
     * A mutable reference (T&) to the element
     * 
     * THROWS:
     * std::out_of_range if (index < 0) or (size_ > index)
     */
    T& operator[](size_type index);

    /**
     * Returns a const reference to the element at the given index
     * 
     * REQUIRES:
     * index is a valid position (0 <= index < size_)
     * 
     * ARGS:
     * index: The position of the element
     * 
     * RETURNS:
     * A immutable reference (const T&) to the element
     */
    const T& operator[](size_type index) const;

    /**
     * Returns a reference to the element at the given index with bounds
     * checking
     * 
     * REQUIRES:
     * index is a valid position (0 <= index < size_)
     * 
     * ARGS:
     * index: The position of the element
     * 
     * RETURNS:
     * A mutuable reference (T&) to the element
     * 
     * THROWS:
     * std::out_of_range if the index is invalid (index >= size_ or index < 0)
     */
    T& at(size_type index);

    /**
     * Returns a const reference to the element at the given index with
     * bounds checking
     * 
     * REQUIRES:
     * index is a valid position (0 <= index <= size_)
     * 
     * ARGS:
     * index: The position of the element
     * 
     * RETURNS:
     * A const reference (const T&) to the element
     * 
     * THROWS:
     * std::out_of_range if the index is invalid (index >= size_ or index < 0)
     */
    const T& at(size_type index) const;

    // ---- Capacity & Size ---- //

    /**
     * Returns the number of elements in the Vector
     * 
     * RETURNS:
     * The current number of elements (size_)
     */
    size_type size() const;

    /**
     * Returns the total storage capacity of the Vector
     * 
     * RETURNS:
     * The current storage capacity (capacity_)
     */
    size_type capacity() const;

    /**
     * Checks if the Vector is emoty
     * 
     * RETURNS:
     * True if the Vector size is 0, otherwise false
     */
    bool empty() const;

    // ---- Modifiers ---- //

    /**
     * Adds a new element to the end of the Vector
     * 
     * ARGS:
     * item: the element to be appended
     * 
     * EFFECTS:
     * The size of the vector will be increased by one. May trigger
     * a reallocation if the capacity is exceeded. Adds the element to
     * the end of the list
     */
    void push_back(const T& item);

    /**
     * Remove the last element from the vector
     * 
     * REQUIRES:
     * The vector is not empty
     * 
     * EFFECTS:
     * The size of the Vector is reduced by one
     * 
     * THROWS:
     * std::out_of_range if size == 0
     */
    void pop_back();

    /**
     * Inserts an element at a specific index
     * 
     * REQUIRES:
     * 0 <= index <= size
     * 
     * ARGS:
     * item: The element to be inserted
     * index: the position where the element will be inserted
     *       - 0 to size-1: inserts in the middle or beginning
     *       - size: inserts at the end (same as push_back)
     * 
     * EFFECTS:
     * Element at and after index are shifted to the right. The size
     * increases by one.
     * 
     * THROWS:
     * std::out_of_range if index > size
     */
    void insert(const T& item, size_type index);

    /**
     * Sets the element at the specific index
     * 
     * REQUIRES:
     * 0 <= index < size
     * 
     * ARGS:
     * item: The element to be set
     * index: the position where the element will be set
     * 
     * EFFECTS:
    */
    void set(const T& item, size_type index);

    /**
     * Removes the element at the specific index
     * 
     * REQUIRES:
     * 0 <= index < size
     * 
     * ARGS:
     * index: the position where the element will be removed
     * 
     * EFFECTS:
     * If the element is not the last element then elements after index
     * are shifted to the left. The size will decrease by one
     */
    void remove(size_type index);

    // ---- ITERATORS ---- //

    /** These methods will allow the Vector to be used with range-based
     * for loops
     */

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    // ---- Private Members ---- //

    private:
    size_type capacity_;
    size_type size_;
    T* array_;
    static constexpr size_type initial_capacity = 10;

    /**
     * Helper function that doubles the size of the array storage when needed
     * 
     * EFFECTS:
     * Allocates new memory, copies all existing elements, and updates capacity_
     */
    void resize();

};

#include "Vector.cpp"

#endif // VECTOR_H_
