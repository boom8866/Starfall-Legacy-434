UPDATE `creature_template` SET `AIName`= '', `scriptname`= 'boss_lord_godfrey' WHERE `entry`= 46964;
UPDATE `creature_template` SET `AIName`= '', `scriptname`= 'npc_sfk_bloodthirsty_ghoul' WHERE `entry`= 50561;
UPDATE `creature_template` SET `flags_extra`= 130, `InhabitType`= 4 WHERE `entry`= 52065;

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(46964, 0, 0, 'Ivar\'s pack failed horribly, so now he sends mercenaries. No matter, your journey ends in agony.', 14, 0, 100, 0, 0, 0, 'Lord Godfrey - Aggro Alliance'),
(46964, 1, 0, 'That bitch Sylvanas sent you too, did she? No matter, your journey ends in agony.', 14, 0, 100, 0, 0, 0, 'Lord Godfrey - Aggro Horde'),
(46964, 2, 0, 'Murder never gets old.', 14, 0, 100, 0, 0, 0, 'Lord Godfrey - Aggro Horde'),
(46964, 2, 1, 'This is the quality of assassin sent to kill me? Laughable.', 14, 0, 100, 0, 0, 0, 'Lord Godfrey - Aggro Horde'),
(46964, 3, 0, '|TInterface\\Icons\\INV_FIREARM_2H_RIFLE_CATACLYSM_B_01.BLP:20|t%s begins to cast |cFFFF0000|Hspell:93520|h[Pistol Barrage]|h|r!', 41, 0, 100, 0, 0, 0, 'Lord Godfrey Pistol Barrage'),
(46964, 4, 0, 'I thank you for the clean death. I would not have done the same...', 14, 0, 100, 0, 0, 0, 'Lord Godfrey');

REPLACE INTO `creature_template_addon` (`entry`, `Auras`) VALUES
(46964, '93597'),
(49712, '93597');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(93707, 'spell_sfk_summon_bloodthirsty_ghouls'),
(93520, 'spell_sfk_pistol_barrage');

DELETE FROM `conditions` WHERE `SourceEntry`= 93564;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 2, 93564, 0, 0, 31, 0, 3, 50561, 0, 0, 0, '', 'Pistol Barrage - Target Bloodthirsty Ghoul');

REPLACE INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `MaxStanding1`, `RewOnKillRepValue1`, `CurrencyId1`, `CurrencyCount1`) VALUES
(49712, 0, 0, 0, 395, 70); -- 5 Player Heroic
