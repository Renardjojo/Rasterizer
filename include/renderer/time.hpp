#ifndef _TIME_MANAGER_H
#define _TIME_MANAGER_H

#include <SDL2/SDL.h>

#define DEFAULT_FPS_MAX 60

class ChronoDt
{
	public:
		ChronoDt () = default;
		ChronoDt (float delay);
		ChronoDt (const ChronoDt& other) = default;
		virtual ~ChronoDt ();

		 /*----------*/
		/* methode  */
	   /*----------*/

	//update chrono statu with delta time. If delta time == 0. So Chrono is paused
	void update(float delta_time);

	//reset chrono with same delay
	void reset();

		 /*----------*/
		/* accessor */
	   /*----------*/

	//return if time delay is pass
	bool isEnd()	const;

		 /*----------*/
		/* mutator  */
	   /*----------*/

		 /*----------*/
		/* operator */
	   /*----------*/

		 /*----------*/
		/* convertor*/ 
	   /*----------*/

	//public variable (get and set with no effect for class)
	float delay_;
	float time_;

	protected:

	bool isFinish_;			

	private:
};

typedef struct S_FPS
{
	unsigned int	frame;
	ChronoDt		chrono {1000};
	unsigned int 	FPSmax;

} T_FPS;

class TimeManager
{
	public:
		TimeManager (unsigned int FPSmax = DEFAULT_FPS_MAX);
		TimeManager (const TimeManager& other)			= default;
		~TimeManager () 								= default;

		/*----------*/
		/* methode  */
		/*----------*/

		//update current time and add delay to correspond to the good FPS
		void update();

		/*----------*/
		/* accessor */
		/*----------*/

		/*----------*/
		/* mutator  */
		/*----------*/

		/*----------*/
		/* operator */
		/*----------*/

		/*----------*/
		/* convertor*/
		/*----------*/

		//public variable (get and set with no effect for class)
		Uint32 	time_;
		float	dtf_; //delta frame frame


	protected:

		T_FPS	FPS_;

	private:
};

#endif // _TIME_MANAGER_H
