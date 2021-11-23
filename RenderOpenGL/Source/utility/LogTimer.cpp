#include "LogTimer.h"

#include "ImGUI/imgui.h"


void EProfileDebugger::Init()
{
}

void EProfileDebugger::Run()
{
}

void EProfileDebugger::Stop()
{
}

void EProfileDebugger::GUIRun()
{
#ifdef PROFILE
	ImGui::Begin( "Profiler" );
	for ( auto& results : TimerProfileResults )
	{
		char label [50];
		strcpy_s( label, results.Name );
		strcat_s( label, " %.4fms" );
		ImGui::Text( label, results.Time );
	}
	TimerProfileResults.clear();
	ImGui::End();
#endif
}
#ifdef PROFILE
void EProfileDebugger::AddTimer(ProfileResults Result)
{

	Instance().TimerProfileResults.push_back( Result );


}
#endif
