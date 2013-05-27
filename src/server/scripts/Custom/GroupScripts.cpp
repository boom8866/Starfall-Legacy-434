#include "Player.h"
#include "ScriptMgr.h"
#include "Group.h"
#include "Spell.h"

class RemoveBuffs : public GroupScript
{
    public:
        RemoveBuffs() : GroupScript("group_buff_remove") { }

        void OnRemoveMember(Group* group, uint64 guid, RemoveMethod /*method*/, uint64 /*kicker*/, const char* /*reason*/)
        {
            for (std::map<uint32, uint64>::iterator itr = group->m_buffStore.begin(); itr != group->m_buffStore.end();)
            {
                if (itr->second == guid)
                {
                    for (auto member : group->GetMemberSlots())
                        if (member.guid != guid)
                            ObjectAccessor::FindPlayer(member.guid)->RemoveAura(itr->first);

                    group->m_buffStore.erase(itr++);
                }
                else
                {
                    ObjectAccessor::FindPlayer(guid)->RemoveAura(itr->first);
                    ++itr;
                }
            }
        }
};

void AddSC_Group_scripts()
{
    new RemoveBuffs();
}
