#pragma once

#include "as_list.h"

/******************************************************************************
 *
 * FUNCTION DECLARATIONS
 * 
 ******************************************************************************/

/**
 * Create a "array" backed list
 * @param initial size of the buffer
 * @param size for each capacity increase
 * @return a new as_list
 */
as_list * as_arraylist_new(uint32_t, uint32_t);

