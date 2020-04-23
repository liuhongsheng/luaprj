#ifndef _COMMON_LUA_H_
#define _COMMON_LUA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

void error(lua_State *L, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  lua_close(L);
  exit(EXIT_FAILURE);
}

static void stackDump(lua_State *L) {
  int i;
  int top = lua_gettop(L);
  for (i = 1; i <= top; i++) { /* repeat for each level */
    int t = lua_type(L, i);
    switch (t) {
      case LUA_TSTRING: /* strings */
        printf("Stack: index %d value %s", i, lua_tostring(L, i));
        break;
      case LUA_TBOOLEAN: /* booleans */
        printf("Stack: index %d value %s", i,
               lua_toboolean(L, i) ? "true" : "false");
        break;
      case LUA_TNUMBER: /* numbers */
        printf("Stack: index %d value %lf", i, lua_tonumber(L, i));
        break;
      default: /* other values */
        printf("Unkown type, typename %s", lua_typename(L, t));
        break;
    }
    printf(" "); /* put a separator */
  }
  printf("\n"); /* end the listing */
}

#ifdef __cplusplus
}
#endif

#endif