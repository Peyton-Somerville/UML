/**********************************************************************
 *                                                  
 *  Guitar Hero: StringSound implementation and SFML audio output 
 **********************************************************************/

Name: Peyton Somerville

Hours to complete assignment : 8

/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/
I completed the whole assignment successfully. All the notes are playing
the right sound when the associated key is pressed. No exceptions are
thrown, so I believe everything is working properly.


/**********************************************************************
 *  Did you attempt the extra credit parts? Which one(s)?
 *  Successfully or not?  As a pair, or individually?
 **********************************************************************/
I attempted to get the up-frequency chirp, but I could not figure out
how to get that working.
I use a lambda expression in the RingBuffer class to display the buffer.

/**********************************************************************
 *  Did you implement exseptions to check your StringSound 
 *	implementation?
 *  Indicate yes or no, and explain how you did it.
 **********************************************************************/
Yes, an exception is thrown when:
- The StringSound constructor is called with a frequency less than 1.
- The StringSound constructor (with vector as parameter) is called with
init.size() is less than 1.
- tic() or sample() is called with and empty ring buffer

/**********************************************************************
 *  List whatever help (if any) you received from TAs,
 *  classmates, or anyone else.
 **********************************************************************/
I worked alone, but used an online resource to help figure out how to
convert from unicode to ASCII when handling the keyboard string in the 
sf::Event::TextEntered case in my window loop.


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
The biggest problem I had was with getting the vector of vectors to work
with the vector of sf::SoundBuffers and vector of sf::Sounds. I kept
getting the error "vector subscript out of range." I thought this was very
strange since vectors can grow or shrink dynamically. I fixed this problem
by declaring the vectors with a size, like this:
std::vector<std::vector<sf::Int16>> vectSamples(KEYBOARD_SIZE);
KEYBOARD_SIZE being 37 for the 37 notes.

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
I display the image of the notes and their corresponding keys.
Also it takes a little while for the sfml window to get ready after being
compiled, but it will load eventually and work properly.