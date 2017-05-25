// Generated by gencpp from file lab4/jint_control_srvResponse.msg
// DO NOT EDIT!


#ifndef LAB4_MESSAGE_JINT_CONTROL_SRVRESPONSE_H
#define LAB4_MESSAGE_JINT_CONTROL_SRVRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace lab4
{
template <class ContainerAllocator>
struct jint_control_srvResponse_
{
  typedef jint_control_srvResponse_<ContainerAllocator> Type;

  jint_control_srvResponse_()
    : status()  {
    }
  jint_control_srvResponse_(const ContainerAllocator& _alloc)
    : status(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _status_type;
  _status_type status;




  typedef boost::shared_ptr< ::lab4::jint_control_srvResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::lab4::jint_control_srvResponse_<ContainerAllocator> const> ConstPtr;

}; // struct jint_control_srvResponse_

typedef ::lab4::jint_control_srvResponse_<std::allocator<void> > jint_control_srvResponse;

typedef boost::shared_ptr< ::lab4::jint_control_srvResponse > jint_control_srvResponsePtr;
typedef boost::shared_ptr< ::lab4::jint_control_srvResponse const> jint_control_srvResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::lab4::jint_control_srvResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::lab4::jint_control_srvResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace lab4

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::lab4::jint_control_srvResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::lab4::jint_control_srvResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::lab4::jint_control_srvResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::lab4::jint_control_srvResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::lab4::jint_control_srvResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::lab4::jint_control_srvResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::lab4::jint_control_srvResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "4fe5af303955c287688e7347e9b00278";
  }

  static const char* value(const ::lab4::jint_control_srvResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x4fe5af303955c287ULL;
  static const uint64_t static_value2 = 0x688e7347e9b00278ULL;
};

template<class ContainerAllocator>
struct DataType< ::lab4::jint_control_srvResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "lab4/jint_control_srvResponse";
  }

  static const char* value(const ::lab4::jint_control_srvResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::lab4::jint_control_srvResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string status\n\
\n\
";
  }

  static const char* value(const ::lab4::jint_control_srvResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::lab4::jint_control_srvResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.status);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct jint_control_srvResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::lab4::jint_control_srvResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::lab4::jint_control_srvResponse_<ContainerAllocator>& v)
  {
    s << indent << "status: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.status);
  }
};

} // namespace message_operations
} // namespace ros

#endif // LAB4_MESSAGE_JINT_CONTROL_SRVRESPONSE_H
