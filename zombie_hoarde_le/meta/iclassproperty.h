#ifndef ICLASSPROPERTY_H
#define ICLASSPROPERTY_H

#include <QVariant>

#include <cassert>
#include <string>

class IClassPropertyBase
{
  public:
    virtual QVariant  getValue(const void* object)                  = 0;
    virtual void      setValue(void* object, const QVariant &value) = 0;

    virtual ~IClassPropertyBase() {}

};

template <typename Class, typename PropertyT>
class IClassProperty : public IClassPropertyBase
{
  public:
    using ClassT        = Class;
    using MemberT       = typename std::decay<PropertyT>::type;

    using PointerT      = MemberT ClassT::*;

    using GetterRefT    = const MemberT& (ClassT::*)() const;
    using SetterRefT    = void (ClassT::*)(const MemberT &);

    using GetterValT    = MemberT (ClassT::*)() const;
    using SetterValT    = void (ClassT::*)(MemberT);

    using NonConstGT    = MemberT& (ClassT::*)();
    using NonConstST    = void (ClassT::*)(MemberT &);

  public:
    static IClassProperty* make(PointerT ptr)
    {
      return new IClassProperty<Class, PropertyT>(ptr);
    }

  public:
    PointerT    m_Pointer;
    GetterRefT  m_GetterRef;
    SetterRefT  m_SetterRef;
    GetterValT  m_GetterVal;
    SetterValT  m_SetterVal;
    NonConstGT  m_NonConstG;
    NonConstST  m_NonConstS;

  public:
    explicit IClassProperty(PointerT ptr) :
      m_Pointer(ptr),
      m_GetterRef(nullptr),
      m_SetterRef(nullptr),
      m_GetterVal(nullptr),
      m_SetterVal(nullptr),
      m_NonConstG(nullptr),
      m_NonConstS(nullptr)
    {
    }

    bool isProperty() const
    {
      return ((this->m_Pointer == nullptr) &&
              (this->m_GetterRef == nullptr && this->m_NonConstG == nullptr) &&
              (this->m_SetterRef == nullptr && this->m_NonConstS == nullptr));
    }

    template <typename T>
    constexpr bool is() const
    {
      return std::is_same<typename std::decay<MemberT>::type, typename std::decay<T>::type>::value;
    }

    template <typename T1, typename T2>
    IClassProperty &addGetterSetter(T1 getterPtr, T2 setterPtr)
    {
      this->addGetter(getterPtr);
      this->addSetter(setterPtr);
      return (*this);
    }

    IClassProperty &addGetter(GetterRefT getterPtr)
    {
      this->m_GetterRef = getterPtr;
      return (*this);
    }

    IClassProperty &addGetter(GetterValT getterPtr)
    {
      this->m_GetterVal = getterPtr;
      return (*this);
    }

    IClassProperty &addGetter(NonConstGT getterPtr)
    {
      this->m_NonConstG = getterPtr;
      return (*this);
    }

    IClassProperty &addGetter(std::nullptr_t)
    {
      this->m_GetterRef = nullptr;
      this->m_GetterVal = nullptr;
      this->m_NonConstG = nullptr;
      return (*this);
    }

    IClassProperty &addSetter(SetterRefT setterPtr)
    {
      this->m_SetterRef = setterPtr;
      return (*this);
    }

    IClassProperty &addSetter(SetterValT setterPtr)
    {
      this->m_SetterVal = setterPtr;
      return (*this);
    }

    IClassProperty &addSetter(NonConstST setterPtr)
    {
      this->m_NonConstS = setterPtr;
      return (*this);
    }

    IClassProperty &addSetter(std::nullptr_t)
    {
      this->m_SetterRef = nullptr;
      this->m_SetterVal = nullptr;
      this->m_NonConstS = nullptr;
      return (*this);
    }

    const MemberT &get(const ClassT &object) const
    {
      if (this->m_GetterRef)
      {
        return (object.*m_GetterRef)();
      }
      else if (this->m_Pointer)
      {
        return object.*m_Pointer;
      }
      else if (this->m_NonConstG)
      {
        return (const_cast<ClassT &>(object).*m_NonConstG)();
      }

      assert(this->m_Pointer && "MemberT::get -> Member doesn't have member ptr or getter!");

      return object.*m_Pointer;
    }

    MemberT &getRef(ClassT &object) const
    {
      if (this->m_NonConstG)
      {
        return (object.*m_NonConstG)();
      }
      else if (this->m_GetterRef)
      {
        return const_cast<MemberT &>(((object.*m_GetterRef)()));
      }

      assert(this->m_Pointer && "MemberT::getRef -> Member doesn't have member ptr or getter!");

      return object.*m_Pointer;
    }

    MemberT getVal(const ClassT &object) const
    {
      if (this->m_GetterVal)
      {
        return (object.*m_GetterVal)();
      }
      else if (this->m_GetterRef)
      {
        return (object.*m_GetterRef)();
      }
      else if (this->m_NonConstG)
      {
        return (const_cast<ClassT &>(object).*m_NonConstG)();
      }

      assert(this->m_Pointer && "MemberT::getVal -> Member doesn't have member ptr or getter!");

      return object.*m_Pointer;
    }

    void set(ClassT& object, const MemberT &value) const
    {
      if (this->m_SetterRef)
      {
        (object.*m_SetterRef)(value);
      }
      else if (this->m_SetterVal)
      {
        (object.*m_SetterVal)(value);
      }
      else if (this->m_NonConstS)
      {
        (object.*m_NonConstS)(const_cast<MemberT &>(value));
      }
      else if (this->m_Pointer)
      {
        object.*m_Pointer = value;
      }
    }

  public:
    QVariant getValue(const void* object) override
    {
      return QVariant(this->getVal(*(ClassT *)object));
    }

    void setValue(void* object, const QVariant& value) override
    {
      if (value.canConvert<PropertyT>())
        this->set(*(ClassT *)object, value.value<PropertyT>());
    }

};

#endif // ICLASSPROPERTY_H
