#include "time.hpp"

ChronoDt::ChronoDt (float delay)
	:	delay_	(delay/1000),
		time_	(0.),
		isFinish_(false)
{}

ChronoDt::~ChronoDt ()
{}

void ChronoDt::update(float delta_time)
{
	isFinish_ = time_ > delay_;

	if (time_ > delay_)
		return;

	time_ += delta_time;
}

bool ChronoDt::isEnd() const
{
	return isFinish_;
}

void ChronoDt::reset()
{
	isFinish_ 	= false;
	time_ 		= 0;
}


TimeManager::TimeManager (unsigned int FPSmax)
	:	time_		(SDL_GetTicks()),
		dtf_		(0.f),
		FPS_		({0, {1000}, FPSmax})
{}

void TimeManager::update()
{
 	dtf_ = (time_ > 0) ? ((SDL_GetTicks() - time_) / 1000.f) : 1.0f / 60.0f;
	
	float delay = ((1/(float)FPS_.FPSmax)*1000) - (dtf_*1000);
	
	if(delay <= 0.)
		delay = 1.;

	SDL_Delay(delay);

	dtf_ += delay/1000;
	

	time_ = SDL_GetTicks();

	FPS_.chrono.update (dtf_);

	if(FPS_.chrono.isEnd())
	{
		FPS_.chrono.reset();
		printf("FPS : %d\nDelta time : %f\n", FPS_.frame, dtf_);
		FPS_.frame = 0;
	}

	FPS_.frame++;
}