#pragma once

#include "Macro.h"

class TestEntity
{
public:
	TestEntity() { LOG_MESSAGE("Test Entity Created"); }
	~TestEntity() { LOG_MESSAGE("Test Entity Deleted"); }

	void print() { LOG_MESSAGE("Test Entity Print"); }
};