#pragma once

namespace FR::GUI
{
	class FRIDrawable
	{
	public:
		virtual void Draw() = 0;

	public:
		virtual ~FRIDrawable() = default;

	};
}

