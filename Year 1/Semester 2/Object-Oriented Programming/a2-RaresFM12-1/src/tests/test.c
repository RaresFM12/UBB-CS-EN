#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "test.h"
#include "service.h"
#include "repository.h"
#include "vector.h"



void test_add_element()
{
	Vector* v = createDefaultVector(&destroyCountry);
	Country* c = createCountry("afe", "fwaef", 24);
	addElement(v, c);

	assert(v->elem[0] == c);
	destroyVector(v);
}

void test_delete_element()
{
	Vector* v = createDefaultVector(&destroyCountry);
	Country* c = createCountry("afe", "fwaef", 24);
	addElement(v, c);
	deleteElement(v, 0);

	assert(v->size == 0);
	destroyVector(v);
}

void test_add_service()
{
	Country* c = createCountry("ffw", "fwfew", 123);
	Repository* r = createRepository();
	Service* s = createService(r);
	addCountryService(s, c, false);

	assert(r->v->size == 1);
	destroyService(s);
}

void test_delete_service()
{
	Country* c = createCountry("ffw", "fwfew", 123);
	Repository* r = createRepository();
	Service* s = createService(r);
	addCountryService(s, c, false);
	deleteCountryService(s, "ffw", false);

	assert(r->v->size == 0);
	destroyService(s);
}

void test_update_service()
{
	Country* c = createCountry("ffw", "fwfew", 123);
	Repository* r = createRepository();
	Service* s = createService(r);
	addCountryService(s, c, false);
	updateCountryService(s, "ffw", 100, false);

	assert(getPopulation(r->v->elem[0]) == 100);
	destroyService(s);
}

void test_add_repo()
{
	Country* c = createCountry("ffw", "fwfew", 123);
	Repository* r = createRepository();
	addCountry(r, c);

	assert(r->v->size == 1);
	destroyRepository(r);
}

void test_delete_repo()
{
	Country* c = createCountry("ffw", "fwfew", 123);
	Repository* r = createRepository();
	addCountry(r, c);
	deleteCountry(r, 0);

	assert(r->v->size == 0);
	destroyRepository(r);
}

void test_update_repo()
{
	Country* c = createCountry("ffw", "fwfew", 123);
	Repository* r = createRepository();
	addCountry(r, c);
	updateCountry(r, "ffw", 200);

	assert(getPopulation(r->v->elem[0]) == 200);
	destroyRepository(r);
}

void test_undo()
{
	Country* c = createCountry("ffw", "fwfew", 123);
	Repository* r = createRepository();
	Service* s = createService(r);
	addCountryService(s, c, true);
	undo(s);

	assert(r->v->size == 0);
	destroyService(s);
}

void test_redo()
{
	Country* c = createCountry("ffw", "fwfew", 123);
	Repository* r = createRepository();
	Service* s = createService(r);
	addCountryService(s, c, true);
	undo(s);
	redo(s);

	assert(r->v->size == 1);
	destroyService(s);
}

void test_all()
{
	test_add_element();
	test_delete_element();
	test_add_service();
	test_delete_service();
	test_update_service();
	test_add_repo();
	test_delete_repo();
	test_update_repo();
	test_undo();
	test_redo();
}


