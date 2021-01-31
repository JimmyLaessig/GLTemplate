#pragma once

#include "Delegate.h"

//#include <concepts>

/** Constructs a private class member with 
 * @param MemberType The type of the member field
 * @param MemberName The name of the member field
 * @param SetFunctionAccessModifier The access modifier for the set function of the Member (public, private, protected)
 */
#define MemberProperty(MemberType, MemberName, SetFunctionAccessModifier)   \
private:                                                                    \
                                                                            \
    Type mMemberName;                                                       \
                                                                            \
    DelegateImpl<MemberType>mMemberNameDelegate;                            \
                                                                            \
public:                                                                     \
                                                                            \
    /* Returns the name of the property */                                  \
    const std::string_view getPropertyName() const                          \
    {                                                                       \
        return "MemberName";                                                \
    }                                                                       \
                                                                            \
    /* Return the value of MemberName */                                    \
    const MemberType& getMemberName() const                                 \
    {                                                                       \
        return mMemberName;                                                 \
    }                                                                       \
                                                                            \
    /* Return the delegate for MemberName */                                \
    IDelegate<Type>& onMemberNameChanged()                                  \
    {                                                                       \
        return mNameDelegate;                                               \
    }                                                                       \
                                                                            \
SetFunctionAccessModifier:                                                  \
    /* Set the value of MemberName */                                       \
    void setName(const Type& value)                                         \
    {                                                                       \
        mName = value;                                                      \
        mNameDelegate.broadcast(mName);                                     \
    }                                                                       \


//// Empty class that, if used as AccessorType of a ValueWithDelegate,
//// enables unrestricted access to setValue()
//class UnrestrictedAccessClass final {};
//
//
//template<typename T>
//concept UnrestrictedAccess = std::is_same_v<UnrestrictedAccessClass, T>;
//
//
//template<typename T>
//concept RestrictedAccess = !std::is_same_v<UnrestrictedAccessClass, T>;
//
//
//template<typename ValueType, typename AccessorType = UnrestrictedAccessClass>
//class ValueWithDelegate
//{
//public:
//    // Friending the AccessorType allows the accessor to call setValue()
//    // eventhough the function is private.
//    friend AccessorType;
//
//    // Construct the class with an initial value
//    ValueWithDelegate(const ValueType& value) : mValue(value) {}
//
//
//    // Prohibit the copying of the class
//    ValueWithDelegate(const ValueWithDelegate& other) = delete;
//
//
//    // Prohibit assigning an pre-existing class with a new one
//    ValueWithDelegate& operator=(const ValueWithDelegate& other) = delete;
//
//
//    // Gets the current value
//    const ValueType& getValue() const
//    {
//        return mValue;
//    }
//
//
//    // Subscribed callback functions are executed if the value changes.
//    template<typename Functor>
//    void subscribe(Functor callback)
//    {
//        mDelegate.subscribe(callback);
//    }
//
//
//    // Public interface of setValue()
//    // Enabled if the UnrestrictedAccess concept applies
//    void setValue(const ValueType& value) requires UnrestrictedAccess<AccessorType>
//    {
//        setValue_Implementation(value);
//    }
//
//private:
//
//    // Private interface of setValue()
//    // Enabled if the UnrestrictedAccess concept does NOT apply
//    void setValue(const ValueType& value) requires RestrictedAccess<AccessorType>
//    {
//        setValue_Implementation(value);
//    }
//
//
//    // Actual implementation of setValue() Don't call this directly
//    void setValue_Implementation(const ValueType& value)
//    {
//        mValue = value;
//        mDelegate.broadcast(mValue);
//    }
//
//
//    ValueType mValue;
//
//    DelegateImpl<ValueType> mDelegate;
//};