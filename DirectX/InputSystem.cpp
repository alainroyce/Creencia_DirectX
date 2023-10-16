#include "InputSystem.h"
#include <Windows.h>

InputSystem::InputSystem()
{
}


InputSystem::~InputSystem()
{
}

void InputSystem::update()
{
	// gets the recent
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	// assigns the first current_mouse_pos to the old_mouse_pos
	if (m_first_time)
	{
		m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
		m_first_time = false;
	}

	// check if there is a difference in the old_mouse_pos to the current_mouse_pos
	if (current_mouse_pos.x != m_old_mouse_pos.m_x || current_mouse_pos.y != m_old_mouse_pos.m_y)
	{
		// There is a MOUSE EVENT
		std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

		while (it != m_set_listeners.end())
		{
			(*it)->onMouseMove(Point(current_mouse_pos.x, current_mouse_pos.y));
			++it;
		}
	}
	// update our old_mouse_pos
	m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);

	// check if there is an active state in our keys
	if (::GetKeyboardState(m_keys_state))
	{
		// iterate all the keys from our keyboard
		for (unsigned int i = 0; i < 256; i++)
		{
			// KEY IS DOWN
			if (m_keys_state[i] & 0x80)
			{
				std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

				while (it != m_set_listeners.end())
				{
					// if left mouse button is clicked
					if (i == VK_LBUTTON)
					{
						// call event
						if (m_keys_state[i] != m_old_keys_state[i])
							(*it)->onLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					// if right mouse button is clicked
					else if (i == VK_RBUTTON)
					{
						// call event
						if (m_keys_state[i] != m_old_keys_state[i])
							(*it)->onRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					else
					{
						// call event
						(*it)->onKeyDown(i);
					}
					++it;
				}
			}
			else // KEY IS UP
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

					while (it != m_set_listeners.end())
					{
						// if left mouse button is released
						if (i == VK_LBUTTON)
						{
							// call event
							(*it)->onLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
						// if right mouse button is released
						if (i == VK_RBUTTON)
						{
							// call event
							(*it)->onRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
						else
						{
							// call event
							(*it)->onKeyUp(i);
						}
						++it;
					}
				}

			}

		}
		// store current keys state to old keys state buffer
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

// add the subscriber to our inputSystem
void InputSystem::addListener(InputListener* listener)
{
	m_set_listeners.insert(listener);
}

// remove the subscriber to our inputSystem
void InputSystem::removeListener(InputListener* listener)
{
	m_set_listeners.erase(listener);
}

void InputSystem::setCursorPosition(const Point& pos)
{
	::SetCursorPos(pos.m_x, pos.m_y);
}

void InputSystem::showCursor(bool show)
{
	::ShowCursor(show);
}

// return the reference of the singleton's instance
InputSystem* InputSystem::get()
{
	static InputSystem system;
	return &system;
}