#pragma once
#include "repository.h"
#include "service_admin.h"
#include "service_user.h"
#include "vector.h"
#include "event.h"
#include "date.h"
#include <cassert>

class Test {
public:

	/// <summary>
	/// Runs all the tests
	/// </summary>
	void run_all();

	/// <summary>
	/// Tests add in a vector
	/// </summary>
	void TestDynamicVector();

	/// <summary>
	/// Tests the datetime
	/// </summary>
	void TestDate();

	/// <summary>
	/// Tests the event
	/// </summary>
	void TestEvent();

	/// <summary>
	/// Tests admin service
	/// </summary>
	void TestAdminService();

	/// <summary>
	/// Tests user service
	/// </summary>
	void TestUserService();

	/// <summary>
	/// Tests the repository
	/// </summary>
	void TestRepository();
};
