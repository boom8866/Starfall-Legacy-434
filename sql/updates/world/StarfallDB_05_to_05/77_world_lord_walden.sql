UPDATE `creature_template` SET `AIName`= '', `scriptname`= 'boss_lord_walden' WHERE `entry`= 46963;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 14, `faction_H`= 14, `flags_extra`= 130, `modelid1`= 1126, `modelid2`= 23767, `InhabitType`= 4, `unit_flags`= unit_flags | 256 | 512 WHERE `entry`= 50522;

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(46963, 0, 0, 'Even here I find myself beset by fools!', 14, 0, 100, 0, 0, 0, 'Lord Walden - Aggro'),
(46963, 1, 0, 'This childish effort ends now!', 14, 0, 100, 0, 0, 0, 'Lord Walden - Slay 1'),
(46963, 1, 1, 'You shall annoy me no longer!', 14, 0, 100, 0, 0, 0, 'Lord Walden - Slay 2'),
(46963, 2, 0, 'My new life was just beginning...', 14, 0, 100, 0, 0, 0, 'Lord Walden - Death');


DELETE FROM `conditions` WHERE `SourceEntry` IN (93599, 93594);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 93599, 0, 0, 31, 0, 3, 46963, 0, 0, 0, '', 'Toxic Coagulant - Target Lord Walden'),
(13, 7, 93594, 0, 0, 31, 0, 3, 46963, 0, 0, 0, '', 'Toxic Cataclyst - Target Lord Walden'),
(13, 7, 93594, 1, 0, 31, 0, 3, 49711, 0, 0, 0, '', 'Toxic Cataclyst - Target Lord Walden');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(93617, 'spell_sfk_toxic_coagulant');

REPLACE INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `MaxStanding1`, `RewOnKillRepValue1`, `CurrencyId1`, `CurrencyCount1`) VALUES
(49711, 0, 0, 0, 395, 70); -- 5 Player Heroic
