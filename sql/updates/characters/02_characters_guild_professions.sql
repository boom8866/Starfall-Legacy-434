ALTER TABLE guild_member ADD ProfessionSkillId0 INT(10) unsigned DEFAULT '0' AFTER BankRemSlotsTab7;
ALTER TABLE guild_member ADD ProfessionLevel0 INT(10) unsigned DEFAULT '0' AFTER ProfessionSkillId0;
ALTER TABLE guild_member ADD ProfessionRank0 INT(10) unsigned DEFAULT '0' AFTER ProfessionLevel0;
ALTER TABLE guild_member ADD ProfessionSkillId1 INT(10) unsigned DEFAULT '0' AFTER ProfessionRank0;
ALTER TABLE guild_member ADD ProfessionLevel1 INT(10) unsigned DEFAULT '0' AFTER ProfessionSkillId1;
ALTER TABLE guild_member ADD ProfessionRank1 INT(10) unsigned DEFAULT '0' AFTER ProfessionLevel1;
