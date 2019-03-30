#include"InputManager.h"
#include "GLib.h"

static unsigned KeyId;
static bool IsDown;

void InputManager::TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
	KeyId = i_VKeyID;
	IsDown = bWentDown;

	#ifdef _DEBUG
		const size_t	lenBuffer = 65;
		char			Buffer[lenBuffer];
	
		//sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
		//OutputDebugStringA(Buffer);
		DEBUG_PRINT("Key: %d is %c", i_VKeyID, (char)i_VKeyID);
		
	#endif // __DEBUG
}

void InputManager::InitService()
{
	GLib::SetKeyStateChangeCallback(TestKeyCallback);
}

// Returns true when the key is down/ Pressed state
bool InputManager::getKeyDown(char i_Key)
{
	if (KeyId == (int)i_Key && IsDown)
		return true;
	return NULL;
}

// Returns true when the key is UP/ Not Pressed state
bool InputManager::getKeyUP(char i_key)
{
	if (KeyId == (int)i_key && !IsDown)
		return true;
	return NULL;
}