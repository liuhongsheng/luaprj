#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commonlua.h"
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

typedef double data_t;

typedef struct NumArray {
  int capacity;
  int size;
  data_t values[]; /* variable part */
} NumArray;

/*a = new(n)*/
static int newArray(lua_State *L) {
  int n = luaL_checkint(L, 1); /*检查参数是否为int并返回参数值*/
  size_t nbytes = sizeof(NumArray) + n * sizeof(data_t);
  /*分配用户数据并将地址压栈*/
  NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);

  luaL_getmetatable(L, "LuaBook.array"); /*获取元表并压栈*/
  lua_setmetatable(L, -2); /*将栈顶的元表弹出栈并将其设置成用户数据的元表*/

  a->size = n;
  a->capacity = n; /*设置容量*/
  return 1;        /* new userdatum is already on the stack */
}

static NumArray *checkarray(lua_State *L) {
  void *ud = luaL_checkudata(L, 1, "LuaBook.array"); /*取出用户数据*/
  luaL_argcheck(L, ud != NULL, 1, "`array' expected"); /*需要先判断用户数据*/
  return (NumArray *)ud;
}

static double *getelem(lua_State *L) {
  NumArray *a = checkarray(L);

  int index = luaL_checkint(L, 2);
  luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");

  return &a->values[index - 1];
}

/*set(array, index, value)*/
static int setArray(lua_State *L) {
  data_t value = (data_t)luaL_checknumber(L, 3); /*取出value值*/
  *getelem(L) = value; /*注意C中数组下标为0~n-1*/
  lua_pushnumber(L, value);

  return 1;
}

/*val = get(array, index)*/
static int getArray(lua_State *L) {
  lua_pushnumber(L, *getelem(L));
  return 1;
}

static int getSize(lua_State *L) {
  NumArray *a = checkarray(L);
  lua_pushnumber(L, a->size);
  return 1;
}

static int getCapacity(lua_State *L) {
  NumArray *a = checkarray(L);
  lua_pushnumber(L, a->capacity);
  return 1;
}

/*delete(array, index)*/
static int deleteVal(lua_State *L) {
  NumArray *a = checkarray(L);

  int index = luaL_checkint(L, 2); /*取出index值*/
  luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");

  data_t value = a->values[index];

  for (int i = index; i < a->size; i++) {
    a->values[i - 1] = a->values[i];
  }

  a->size--;
  lua_pushnumber(L, value); /*返回被删除位置的值*/

  return 1;
}

/*isnert(array, index, val)*/
static int insertVal(lua_State *L) {
  NumArray *a = checkarray(L);

  int index = luaL_checkint(L, 2); /*取出index值*/
  luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");

  data_t value = luaL_checknumber(L, 3); /*取出value值*/

  if (a->size >= a->capacity) {
    luaL_error(L, "array is full, size %d, capacity %d", a->size, a->capacity);
  }

  for (int i = a->size - 1; i >= index - 1; i--) {
    a->values[i + 1] = a->values[i];
  }

  a->values[index - 1] = value;
  a->size++;
  lua_pushnumber(L, value); /*返回被插入的值*/

  return 1;
}

/*empty(array)*/
static int isEmpty(lua_State *L) {
  NumArray *a = checkarray(L);

  bool isEmpty = (0 == a->size) ? true : false;
  lua_pushboolean(L, isEmpty);

  return 1;
}

static const struct luaL_reg arraylib_f[] = {{"new", newArray}, {NULL, NULL}};

static const struct luaL_reg arraylib_m[] = {
    {"set", setArray},         {"get", getArray},     {"size", getSize},
    {"capacity", getCapacity}, {"delete", deleteVal}, {"insert", insertVal},
    {"empty", isEmpty},        {NULL, NULL}};

// luaopen_xxx, xxx和require后面的虚拟模块名必须一致
int luaopen_array(lua_State *L) {
  /*以面向对象的方式调用方法*/
  luaL_newmetatable(L, "LuaBook.array"); /*create new metatable*/
  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2); /* pushes the metatable */
  lua_settable(L, -3);  /* metatable.__index = metatable */

  /*第一次调用luaL_openlib，当第一个函数为NULL时，会将栈中低于upvalues值的下一个位置的表作为create
    table,并将方法打包 类似于metatable = {"set"=setArray， ....}
  */
  luaL_openlib(L, NULL, arraylib_m, 0);
  luaL_openlib(L, "array", arraylib_f, 0);/*create packed table array = {"new" = newArray}*/
  return 1;
}