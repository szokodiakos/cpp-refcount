#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

/**
 * @class StringValue
 * @author Akos Szokodi
 * @date 04/05/15
 * @file MyString.h
 * @brief Holds a char* data, with additional reference counter.
 */
class StringValue {

private:

    /**
    * @brief char* which holds the string.
    */
    char *data;

    /**
    * @brief Counts how many objects (MyStrings) are referring to this particular StringValue.
    * If the counter reaches zero, the StringValue can be destroyed.
    */
    int refCount;

public:

    /**
    * @brief Creates empty ("") StringValue with 1 reference count.
    */
    StringValue();

    /**
    * @brief Copy constructor.
    * @param other The StringValue to be copied.
    */
    StringValue(const StringValue& other);

    /**
     * @brief Creates StringValue from const char* with 1 reference count.
     * @param string Adds trailing '\0' to the string.
     */
    StringValue(const char* string);

    /**
     * @brief Destructor, deletes the data field.
     */
    ~StringValue();

    /**
     * @brief Assignment operator.
     * @param rhs The StringValue to be assigned.
     * @return The modified StringValue.
     */
    StringValue& operator= (StringValue rhs);

    /**
     * @brief Indexing operator to read/modify individual chars from data.
     * @param index From 0 To size of data array - 1.
     * @return The character at the desired poisition (if exists).
     */
    char& operator[] (int index);

    /**
     * @brief Gets the refCount field.
     * @return refCount field's value.
     */
    int getRefCount() const;

    /**
     * @brief Gets the data field.
     * @return data field's value.
     */
    char* getData() const;

    /**
     * @brief Increments reference counter by one.
     */
    void incrementRefCount();

    /**
     * @brief Decrements reference counter by one.
     */
    void decrementRefCount();

    /**
     * @brief Concatenates two StringValues by concatenating their datas (adds the trailing '\0').
     * @param lhs Left operand
     * @param rhs Right operand
     * @return The concatenated StringValue.
     */
    friend StringValue operator+ (const StringValue& lhs, const StringValue& rhs);
};

/**
* @class MyString
* @author Akos Szokodi
* @date 04/05/15
* @file MyString.h
* @brief Custom String class, which handles a StringValue.
*/
class MyString {

private:

    /**
     * @brief Pointer to a StringValue.
     */
    StringValue *value;

public:

    /**
     * @brief Creates a MyString with an empty StringValue.
     */
    MyString();

    /**
     * @brief Creates a MyString with a StringValue initialized with a const char*.
     * @param string The parameter passed to StringValue's constructor.
     */
    MyString(const char* string);

    /**
     * @brief Creates a MyString with a StringValue.
     * @param stringValue The parameter passed to StringValue's copy constructor.
     */
    MyString(StringValue& stringValue);

    /**
     * @brief Copy constructor.
     * @param other The MyString to be copied.
     */
    MyString(const MyString& other);

    /**
     * @brief Move constructor.
     * @param other The MyString to be moved.
     */
    MyString(MyString && other);

    /**
     * @brief Destructor, deletes the value field (if exists).
     * The value field can be a nullptr, because of the move semantics.
     */
    ~MyString();

    /**
     * @brief Assignment operator.
     * @param rhs The MyString to be assigned.
     * @return The modified MyString.
     */
    MyString& operator= (MyString rhs);

    /**
     * @brief Concatenates the object's StringValue with a MyString's StringValue on the right hand side.
     * @param rhs The MyString to be concatenated.
     * @return MyString concatenated with another MyString.
     */
    MyString& operator+= (const MyString& rhs);

    /**
     * @brief Concatenates the object's StringValue with the const char* on the right hand side.
     * @param string The const char* string to be concatenated.
     * @return MyString concatenated with a const char*.
     */
    MyString& operator+= (const char* string);

    /**
     * @brief Concatenates the object's StringValue with the c character on the right hand side.
     * @param c The character to be concatenated.
     * @return MyString concatenated with a character.
     */
    MyString& operator+= (char c);

    /**
     * @brief Retrieves the object's StringValue's desired character.
     * @param index From 0 To size of StringValue's data array - 1.
     * @return The character at the desired index (if exists).
     */
    char& operator[] (int index);

    /**
     * @brief Retrieves the object's StringValue's desired character for read-only purposes.
     * @param index From 0 To size of StringValue's data array - 1.
     * @return The read-only character at the desired index (if exists).
     */
    const char& operator[] (int index) const;

    /**
     * @brief Returns the object's StringValue.
     * @return The object's value field.
     */
    StringValue* getValue();

    /**
     * @brief Returns the object's StringValue's data length (using strlen)
     * @return The length of the value's data length.
     */
    int getLength() const;

    /**
     * @brief Unlinks the object from its value. First it decrements the
     * pointed StringValue's reference counter, then if this number becomes zero,
     * (which means this object was the last object which referred to that
     * StringValue), the object's responsibility to delete the StringValue.
     */
    void unlinkStringValue();

    /**
     * @brief Concatenates two MyString objects by concatenating their StringValues.
     * @param lhs The left operand.
     * @param rhs The right operand.
     * @return The concatenated MyString.
     */
    friend MyString operator+ (const MyString &lhs, const MyString& rhs);

    /**
     * @brief Concatenates a MyString with a const char*, by concatenating the
     * MyString's StringValue to the const char*.
     * @param myString The left operand.
     * @param string The right operand.
     * @return The concatenated MyString.
     */
    friend MyString operator+ (const MyString &myString, const char* string);

    /**
     * @brief Concatenates a MyString with a character, by concatenating the
     * MyString's StringValue to the character.
     * @param myString The left operand.
     * @param c The right operand.
     * @return The concatenated MyString.
     */
    friend MyString operator+ (const MyString &myString, char c);

    /**
     * @brief Printing operator, which prints the MyString value's data.
     * @param os Reference to an output stream.
     * @param myString The MyString object to be printed.
     */
    friend std::ostream& operator<< (std::ostream& os, const MyString& myString);

    /**
     * @brief Scanning operator, which scans the input into the MyString value's data.
     * Currently the buffer size is limited to 256 characters.
     * @param is Reference to an input stream.
     * @param myString The MyString object to be filled with input.
     */
    friend std::istream& operator>> (std::istream& is, MyString& myString);

};

#endif // MYSTRING_H
