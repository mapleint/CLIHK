#pragma once
/* How to use?
 * Hotkeys MUST be in pairs of two
 * Use capital letters for what you type
 * Use lowercase for control keys
 * Important to note by default the command "quit" will have this process end
 *	you can change this with the "quitstr"
 * Only supports AlphaNumeric keys, as well as
 * Control Keys:
 * must be preceeded by l or r for left or right
 * 'a' = ALT
 * 's' = SHiFT
 * 'c' = CONTROL
 * Example:
 * "laS", "start firefox", will start firefox when left alt + S is pressed
 * "lslaL", "start firefox duckduckgo.com", will open duckduckgo in firefox 
 */

#define QUIT "quit"

const char* hkfuncpair[] = {
	/*LSHIFT W QUITS BY DEFAULT*/
	"lsW", QUIT,
	/*Rest are what I use commonly*/
	"rsW", "start firefox duckduckgo.com",
};
