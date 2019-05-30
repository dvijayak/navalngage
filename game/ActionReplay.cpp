#include "ActionReplay.hpp"

#include <fstream>
#include <sstream>
#include <memory>
#include <regex>
#include <algorithm>

#include "Chrono.hpp"

#include "Action.hpp"
#include "ActionTypeIncludes.hpp"

ActionReplay* ActionReplay::s_pInstance(0);

ActionReplay& ActionReplay::Instance ()
{
	if (!s_pInstance)
	{		
		s_pInstance = new ActionReplay();
	}

	return *s_pInstance;
}

void ActionReplay::Destroy ()
{
	if (s_pInstance)
	{
		delete s_pInstance;
	}
}

struct RecorderImpl
{
	RecorderImpl (std::string const& filename="replay.log")
		: logger(0)
	{
		auto sink = std::make_shared<spdlog::sinks::simple_file_sink_st>(filename);
		logger = std::make_shared<spdlog::logger>("replay", sink);
		logger->set_pattern("%v");
	}

	std::shared_ptr<spdlog::logger> logger;
};

ActionReplay::ActionReplay ()
	: m_bActive(false) // by default, we are in normal play mode
	, m_pRecorder(0)
{
	std::stringstream ss;
	ss << "replay_" << Chrono::GetTicksAtStartup() << ".log";
	m_filename = ss.str();	
}

ActionReplay::~ActionReplay ()
{
	if (m_pRecorder)
	{
		delete m_pRecorder;
	}
}

void ActionReplay::RecordAction (Action const& a)
{
	if (m_bActive) // we are in replay mode, so don't record
		return;

	if (!m_pRecorder)
		m_pRecorder = new RecorderImpl(m_filename);

	assert(m_pRecorder && m_pRecorder->logger);

	m_pRecorder->logger->info("{}", a);
}

bool ActionReplay::Activate (std::string const& filename)
{
	m_bActive = false;

	std::ifstream ifs;
	ifs.open(filename);
	if (ifs.is_open())
	{
		if (!ifs.good())
		{
			errlog("Failed to open action replay file '{}'", filename);
		}
		else
		{
			std::string temp;
			temp.reserve(2000); // should be as reasonably high as possible to avoid reallocations for particularly long lines
			while (!ifs.eof())
			{
				ifs >> temp;

				if (!temp.empty())
				{
					ProcessReplayFileLine(temp);
				}

				temp.clear();
			}

			m_bActive = true;
			trclog("Activated action replay mode. Replay file: '{}'", filename);
		}

		ifs.close(); // is this necessary or does ifstream employ RAII?
	}

	return m_bActive;
}

void ActionReplay::ProcessReplayFileLine (std::string& line)
{
	console(line);

	// Current format:
	// (\d+),(\w+Action),(.+=.+,)*
	// $1 = time of action performance (represented as ticks since app startup)
	// $2 = action type (usually is the name of the action class)
	// $3..n = key/value pairs representing action object members
	std::smatch matches1;
	static std::regex r1("^(?:\\s*)(\\d+),(\\w+)(.*)(?:\\s*)$");
	std::regex_search(line, matches1, r1);
	// console("timestamp = {} type = {}", matches1[1], matches1[2]);

	std::string const& fields = matches1[3];
	static std::regex r2("(\\w+=\\w+)");
	if (matches1[2] == "RotateAction")
	{
		// std::vector<std::string> tokens;
		// std::copy(std::sregex_token_iterator(fields.begin(), fields.end(), r2, -1),
		// 	std::sregex_token_iterator(),
		// 	tokens.begin());
		// for (auto const& s : tokens)
		// 	console(s);
		// RotateAction* p = new RotateAction();
		// p->
	}
}

void ActionReplay::Replay ()
{}