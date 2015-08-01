#include "fx/PlaybackManager.h"
#include "fx/VolumeSound.h"

#include <stdexcept> 

AUD_NAMESPACE_BEGIN
PlaybackManager::PlaybackManager(std::shared_ptr<IDevice> device) :
	m_device(device)
{
}

void PlaybackManager::addHandle(std::shared_ptr<IHandle> handle, std::string catName)
{
}

void PlaybackManager::addCategory(std::shared_ptr<PlaybackCategory> category, std::string catName)
{
}

std::shared_ptr<IHandle> PlaybackManager::play(std::shared_ptr<ISound> sound, std::string catName)
{
	std::shared_ptr<PlaybackCategory> category;
	try
	{
		category = m_categories.at(catName);
	}
	catch (std::out_of_range& oor)
	{
		category = std::make_shared<PlaybackCategory>();
		m_categories[catName] = category;
	}
	std::shared_ptr<ISound> vs (std::make_shared<VolumeSound>(sound, category->getSharedVolume()));
	m_device->lock();
	auto handle = m_device->play(vs);
	category->addHandle(handle);
	m_device->unlock();
	return handle;
}

bool PlaybackManager::resume(std::string catName)
{
	try
	{
		m_categories.at(catName)->resume();
		return true;
	}
	catch (std::out_of_range& oor) 
	{
		return false;
	}
}

bool PlaybackManager::pause(std::string catName)
{
	try
	{
		m_categories.at(catName)->pause();
		return true;
	}
	catch (std::out_of_range& oor)
	{
		return false;
	}
}

float PlaybackManager::getVolume(std::string catName)
{
	try
	{
		return m_categories.at(catName)->getVolume();
	}
	catch (std::out_of_range& oor)
	{
		return -1.0;
	}
}

bool PlaybackManager::setVolume(float volume, std::string catName)
{
	try
	{
		m_categories.at(catName)->setVolume(volume);
		return true;
	}
	catch (std::out_of_range& oor)
	{
		return false;
	}
}

bool PlaybackManager::stop(std::string catName)
{
	try
	{
		m_categories.at(catName)->stop();
		return true;
	}
	catch (std::out_of_range& oor)
	{
		return false;
	}
}
AUD_NAMESPACE_END