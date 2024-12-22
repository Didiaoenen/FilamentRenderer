#pragma once

namespace FR::GUI
{
	class FRIPlugin
	{
	public:
		virtual void Execute() = 0;

	public:
		virtual ~FRIPlugin() = default;

	public:
		void* userData{ nullptr };

	};
}