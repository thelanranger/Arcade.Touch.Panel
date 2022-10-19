#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.
DetectHiddenText, On 
DetectHiddenWindows, On 

^+=::			; ctrl + shift + =
send {Volume_Up}	; Increase Master Volume
return

^+-::			; ctrl + shift + -
send {Volume_Down}	; Decrease Master Volume
return

^+M::  			; ctrl + shift + M
SoundSet, 1,, Mute	; Mute Master Volume
return

^+N::  			; ctrl + shift + N
SoundSet, 0,, Mute	; UnMute Master Volume
return


; --Winamp Controls--

;___________PLAY/PAUSE
^+S::
Media_Play_Pause::
SendMessage, 0x400,0,104,,ahk_class Winamp v1.x
	if errorlevel = 0
	{
	SendMessage, 0x111,40045,,,ahk_class Winamp v1.x
	}
	
	else
	{
	SendMessage, 0x111,40046,,,ahk_class Winamp v1.x
	}

return

^+G::   ; Winamp Play
	PostMessage, 0x111,40045,,,ahk_class Winamp v1.x
return

^+H::	; Winamp Pause
	PostMessage, 0x111,40046,,,ahk_class Winamp v1.x
return     

;____________PREVIOUS TRACK
^+A::
Media_Prev::
	PostMessage, 0x111,40044,,,ahk_class Winamp v1.x
return

;_______________NEXT TRACK
^+F::
Media_Next::
	PostMessage, 0x111,40048,,,ahk_class Winamp v1.x
return

;_______________STOP
^+D::
Media_Stop::
	PostMessage, 0x111,40047,,,ahk_class Winamp v1.x
return

;_______________VolumeUp
^+Q::
;Winamp_Volume_Up::
	PostMessage, 0x111,40058,,,ahk_class Winamp v1.x
return

;_______________VolumeDown
^+W::
;Winamp_Volume_Down::
	PostMessage, 0x111,40059,,,ahk_class Winamp v1.x
return




;_______________RUN/CLOSE WINAMP
^+!MButton::
Launch_Media::
	IfWinExist ,ahk_class Winamp v1.x
	{
	PostMessage, 0x111,40001,,,ahk_class Winamp v1.x
	}

	else
	{
	run,C:\Program Files (x86)\Winamp\winamp.exe ;change winamp path here
	}
return

;_________________SEEK FORWARD
^+RButton::
^Media_Next::
	SendMessage, 0x400,0,105,,ahk_class Winamp v1.x
	if errorlevel <> -1
	{
	errorlevel += 5000
	PostMessage, 0x400,%errorlevel%,106,,ahk_class Winamp v1.x
	}
return

;__________________SEEK BACKWARD
^+LButton::
^Media_Prev::
	SendMessage, 0x400,0,105,,ahk_class Winamp v1.x
	if errorlevel <> -1
	{
	errorlevel -= 5000
	PostMessage, 0x400,%errorlevel%,106,,ahk_class Winamp v1.x
	}
return

; --Winamp Controls--


