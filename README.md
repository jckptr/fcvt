# fcvt
File format converter, line terminator, tab expand

this is a small tool that convert text files to another format
when i copy my source code from mswindows to linux, or reverse.
it helps me to finish convertion of line terminator rules.

an incomplete tab expand function is added, 

Usage:

fcvt [-e] [-w|u|m] filename

-e  expand tab '\t' into 4 space

-w  cvt to mswindows line term (CR+LF)

 u  cvt to unix/linux line term (LF)
 
 m  cvt to macos line term (CR)
 
this program will duplicate the source file "filename" into a temp file "__old__filename"
incase sth stupid happens. If it be, you can recover data from the temp file.
