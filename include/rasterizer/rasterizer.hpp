#ifndef _RASTERIZER_HPP
#define _RASTERIZER_HPP

class Rasterizer
{
	public:
		Rasterizer () = default;
		Rasterizer (const Rasterizer& other) = default;
		virtual ~Rasterizer () = default;

		 /*----------*/
		/* methode  */
	   /*----------*/

		/**
		 * function : drawLine
		 *
		 * parameter : 
		 *  : 
		 *  :
		 *
		 * return (type void):
		 *
		 * brief : 
		 */
		void		drawLine		();
		
		/**
		 * function : drawTriangle
		 *
		 * parameter : 
		 *  : 
		 *  :
		 *
		 * return (type void):
		 *
		 * brief : 
		 */
		void		drawTriangle		();
		
		

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

	protected:
			

	private:
};

#endif // _RASTERIZER_HPP
