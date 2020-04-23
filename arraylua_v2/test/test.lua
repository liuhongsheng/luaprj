#!/usr/bin/lua

package.cpath = package.path .. ";./../bin/?.so" --定义C动态库的搜索路径
require "array" --导入动态库

local array = array


local LENGTH = 20
local a = array.new(LENGTH)

--测试size/capacity方法
print("a:", a)
print("size:", a.size(a))
print("capacity:", a.capacity(a))
print("-----------------------------------------------------------------------")


--测试set方法
for i=1,LENGTH do
 a.set(a, i, i*10) 
end


for i = 1, a.size(a) do
	local s = string.format("index: %d, val: %d", i, a.get(a, i))
	print(s)
end
print("-----------------------------------------------------------------------")


--测试delete方法，index位置被delete之后，后面的元素前移
print(string.format("index: %d, val: %d", 10, a.get(a, 10)))
a.delete(a, 10)
print(string.format("index: %d, val: %d", 10, a.get(a, 10)))
print("-----------------------------------------------------------------------")

--测试insert方法，index位置插入元素之后，后面的元素后移
a.insert(a, 5, 520)
print(string.format("index: %d, val: %d", 5, a.get(a, 5)))
print("-----------------------------------------------------------------------")


for i = 1, a.size(a) do
	local s = string.format("index: %d, val: %d", i, a.get(a, i))
	print(s)
end
