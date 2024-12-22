#pragma once

namespace FR::GUI
{
	class FRIDrawable
	{
	public:
		virtual void Draw() = 0;

	protected:
		virtual ~FRIDrawable() = default;

	};
}

