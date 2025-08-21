#pragma once
#include "repository.h"
#include "service_admin.h"
#include "vector.h"
#include "event.h"
#include "date.h"
#include "exceptions.h"
#include "validator.h"
#include "file_repository.h"
#include <cassert>

class Test {
public:

	/// <summary>
	/// Runs all the tests
	/// </summary>
	void run_all();

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
	/// Tests the repository
	/// </summary>
	void TestRepository();

	/// <summary>
	/// Tests the Html format
	/// </summary>
	void TestHtml();

	/// <summary>
	/// Tests if the files work
	/// </summary>
	void TestFile();

	/// <summary>
	/// Tests the exceptions
	/// </summary>
	void TestExceptions();
};
