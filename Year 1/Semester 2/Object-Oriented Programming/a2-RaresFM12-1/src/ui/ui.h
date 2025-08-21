#pragma once
#include <stdio.h>
#include "service.h"

typedef struct {
	Service* service;

} UI;

/// <summary>
/// Contructor of the UI struct
/// </summary>
/// <param name="service">the service</param>
/// <returns>the ui</returns>
UI* createUI(Service* service);

/// <summary>
/// Destructor of the UI struct
/// </summary>
/// <param name="u">the ui</param>
void destroyUI(UI* u);

/// <summary>
/// Prints the menu of the application and and helps the user to interact with the program
/// </summary>
/// <param name="ui">the ui</param>
void startUI(UI* ui);

/// <summary>
/// Adds defaults cases(10 entries for the user)
///</summary>
///<param name="ui">the ui</param>
void addDefaultCountries(UI* ui);