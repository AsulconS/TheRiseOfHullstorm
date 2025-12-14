#pragma once

class Entity;

struct BaseComponent
{
	Entity* entity;
};

template <typename T>
struct Component : public BaseComponent
{
	static const uint32 ID;
	static const uint32 SIZE;
};
