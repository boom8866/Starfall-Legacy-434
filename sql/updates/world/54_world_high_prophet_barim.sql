
UPDATE `creature_template` SET `minlevel`= 86, `maxlevel`= 86, `scriptname`= 'boss_high_prophet_barim' WHERE `entry`= 43612;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16, `exp`= 3 WHERE `entry`= 48951;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16, `scriptname`= 'npc_lct_heavens_fury' WHERE `entry`= 43801;
UPDATE `creature_template` SET `scriptname`= 'npc_lct_blaze_of_the_heavens_dummy' WHERE `entry` IN (48904, 43926);
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16, `exp`= 3, `scriptname`= 'npc_lct_blaze_of_the_heavens' WHERE `entry`= 48906;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16, `modelid1`= 1126, `modelid2`= 11686, `flags_extra`= 130, `scriptname`= 'npc_lct_blaze_fire_dummy' WHERE `entry`= 48907;
UPDATE `creature_template` SET `scriptname`= 'npc_lct_repenteance' WHERE `entry`= 43817;
UPDATE `creature_template` SET `minlevel`= 86, `maxlevel`= 86, `scriptname`= 'npc_lct_harbringer_of_darkness' WHERE `entry`= 43927;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87 WHERE `entry`= 48953;
UPDATE `creature_template` SET `minlevel`= 84, `maxlevel`= 84, `faction_A`= 16, `faction_H`= 16, `exp`= 3, `scriptname`= 'npc_lct_soul_fragment' WHERE `entry`= 43934; -- 48954
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 16, `faction_H`= 16, `exp`= 3 WHERE `entry`= 48954;

DELETE FROM conditions WHERE SourceEntry IN (82263);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 82263, 0, 0, 31, 0, 3, 43927, 0, 0, 0, '', 'Merged Soul - Target Harbinger of Darkness');

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(43612, 0, 0, 'Begone infidels, you are not welcome here!', 14, 0, 100, 0, 0, 19735, 'Barim - Aggro'),
(43612, 1, 0, 'Kneel before me and repent!', 14, 0, 100, 0, 0, 19737, 'High Prophet Barim - Phase 2'),
(43612, 2, 0, 'May peace find you now.', 14, 0, 100, 0, 0, 19738, 'High Prophet Barim - Slay 1'),
(43612, 2, 1, 'The Heavens take you!', 14, 0, 100, 0, 0, 19736, 'High Prophet Barim - Slay 2'),
(43612, 3, 0, 'Death is only the beginning!', 14, 0, 100, 0, 0, 19733, 'High Prophet Barim - Death');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(82506, 'spell_lct_fifty_lashings'),
(82168, 'spell_lct_repenteance_pull');

REPLACE INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `MaxStanding1`, `RewOnKillRepValue1`, `CurrencyId1`, `CurrencyCount1`) VALUES
(43612, 0, 0, 0, 395, 30), -- 5 Player Normal
(48951, 0, 0, 0, 395, 70); -- 5 Player Heroic
