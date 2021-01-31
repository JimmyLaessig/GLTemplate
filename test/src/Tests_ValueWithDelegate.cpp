#include <catch2/catch.hpp>
#include <Application/ValueWithDelegate.h>
//#include "glm/glm.hpp"

//struct S
//{
//	ValueWithDelegate<int, S> field{ 10 };
//
//};
//
//
//
//TEST_CASE("Creating Value with a public delegate")
//{
//	ValueWithDelegate<int> field(10);
//
//	CHECK(field.getValue() == 10);
//	
//	field.setValue(15);
//
//	CHECK(field.getValue() == 15);
//
//	int numCallbackCalls = 0;
//
//	field.subscribe([&](auto value)
//	{
//		CHECK(value == field.getValue());
//		numCallbackCalls++;
//	});
//	field.setValue(20);
//	CHECK(numCallbackCalls == 1);
//}
//
//
//struct DelegateOwner
//{
//	ValueWithDelegate<float, DelegateOwner> field{ 0.5f };
//
//	void setValue(float v) { field.setValue(v); }
//};
//
//
//TEST_CASE("Creating Value with a owned delegate")
//{
//	DelegateOwner owner;
//
//	CHECK(owner.field.getValue() == 0.5f);
//
//	owner.setValue(15);
//
//	CHECK(owner.field.getValue() == 15);
//
//	int numCallbackCalls = 0;
//
//	owner.field.subscribe([&](auto value)
//	{
//		CHECK(value == owner.field.getValue());
//		numCallbackCalls++;
//	});
//	owner.setValue(20);
//	CHECK(numCallbackCalls == 1);
//}


