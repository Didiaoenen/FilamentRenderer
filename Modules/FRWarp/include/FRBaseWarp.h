#pragma once

namespace FR
{
	#define RefValue(ref) ref.Value()
	#define PtrValue(ptr) ptr->Value()

	class FRBaseWarp
	{
	public:
		FRBaseWarp() = default;

	public:
		virtual ~FRBaseWarp() = default;

	};
}