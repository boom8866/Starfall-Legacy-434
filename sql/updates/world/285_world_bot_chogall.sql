
REPLACE INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6444, 'at_chogall_intro');

UPDATE `creature_template` SET `scriptname`= 'boss_chogall' WHERE `entry`= 43324;

UPDATE `creature` SET `phaseMask`= 1 WHERE `id`= 43324;
DELETE FROM `creature_template_addon` WHERE `entry`= 43324;

UPDATE `creature_template` SET `flags_extra`=128, `ScriptName`='npc_bot_shadow_portal' WHERE `entry`=47019;
UPDATE `creature_template` SET `flags_extra`=128, `ScriptName`='npc_bot_fire_portal' WHERE `entry`=43393;
UPDATE `creature_template` SET UPDATE `creature_template` SET `minlevel`=88, `maxlevel`=88, `exp`=3, `faction`=16, `flags_extra`=128, `ScriptName`='npc_bot_blaze' WHERE `entry`=43585;

DELETE FROM `creature_text` WHERE `entry`=43324;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(43324,3,0,'Valiona, Theralion, put them in their place.',14,0,100,0,0,22063,'Cho\'Gall - Theralion and Valiona Intro'),
(43324,4,0,'Welcome, mortals. (Frail little children). Few have laid eyes on this inner sanctum. (They reach out to touch the fire!)',14,0,100,0,0,22065,'Cho\'gall - Ascendant Countil Intro'),
(43324,5,0,'It is here the chosen realize their destiny. (One with eternity). And it is here that you will realize yours.(End of the flesh. End of the flesh)!',14,0,100,0,0,22066,'Cho\'gall - Ascendant Countil Intro'),
(43324,6,0,'Brothers of Twilight! The Hammer calls to you! (Fire water earth air). Leave your mortal shell behind. (Fire water earth air). Embrace your new forms for here and everafter! (Burn and drown and crush and suffocate). And use your gifts to destroy the unbelievers. (Burn and drown and crush and suffocate)!!',14,0,100,0,0,22067,'Cho\'gall - Ascendant Countil Intro'),
(43324,7,0,'Foolish mortals-(Usurper\'s children!) nothing you have done- (Spawn of a lesser god!) I am TRYING to speak here. (Words, words, words. The Master wants murder.) ALL falls to chaos. ALL will be destroyed. (Chaos, chaos!) Your work here today changes nothing. (Chaos, chaos, all things end) No mortal may see what you have and live. Your end has come.',14,0,100,0,0,22068,'Cho\'gall - Cho\'gall Intro'),
(43324,8,0,'Enough! (To His will all flesh succumbs. From His kingdom, chaos comes.) Yes - what he said.',14,0,100,0,0,22081,'Cho\'gall - Aggro'),
(43324,9,0,'Give me your strength!',14,0,100,0,0,22078,'Comment'),
(43324,9,1,'Behold the might of the Hammer!',14,0,100,0,0,22079,'Comment'),
(43324,9,2,'Everyone succumbs in the end!',14,0,100,0,0,22089,'Comment'),
(43324,10,0,'Behold the destiny of your fragile world!',14,0,100,0,0,22084,'Comment'),
(43324,10,1,'(Come brothers! Feast on hope!)',14,0,100,0,0,22086,'Comment'),
(43324,10,2,'More, more! (More! They need more!)',14,0,100,0,0,22085,'Comment'),
(43324,11,0,'Brother... it cannot be... (Destiny has come!) My strength... (Too proud! He speaks in blood! Listen!) My mind... (It is for His glory we serve!) What... is happening...? (Gone is the dawn. Come shades of twilight! Come madness! Come Havoc! Come infinite night!)',14,0,100,0,0,22093,'Comment'),
(43324,12,0,'(The claws of fate grasp the unbelievers!!)',14,0,100,0,0,22094,'Comment'),
(43324,12,1,'What madness have we wrought... (Not yet enough!)',14,0,100,0,0,22096,'Comment'),
(43324,12,2,'I can\'t take much more... (Brother, it merely begins!!)',14,0,100,0,0,22097,'Comment'),
(43324,12,3,'(The master SEES!! The master SEES!!!) ',14,0,100,0,0,22095,'Comment'),
(43324,12,4,'(The master\'s eye sees all that was and all to be, or not!)',14,0,100,0,0,22098,'Comment'),
(43324,13,0,'Cho\'gall cackles maniacally.',16,0,100,0,0,0,'Comment'),
(43324,13,1,'(NOW they see the darkness! Their eyes are open!!)',14,0,100,0,0,22090,'Comment'),
(43324,13,2,'Now the master has them!',14,0,100,0,0,22091,'Comment'),
(43324,13,3,'(Chaos! Madness! Like a hug for your brain!!)',14,0,100,0,0,22091,'Comment'),
(43324,14,0,'It is finished. (The fate of all!)',14,0,100,0,0,22101,'Comment'),
(43324,15,0,'Brother... we are shattered... (But the master... I still hear... so angry... Master...)',14,0,100,0,0,22099,'Comment'),
(43324,16,0,'Cho\'gall beckons and casts |cFF006EFD|Hspell:91303|h[Conversion]|h|r!',41,0,100,0,0,0,'Comment'),
(43324,17,0,'|TInterface\\Icons\\spell_shadow_shadesofdarkness.blp:20|t%s begins to summon |cFFFF0000Darkened Creations|r to aid him!',41,0,100,0,0,0,'Comment');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (91303, 93203, 93204, 93205);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(91303, 'spell_bot_conversion'),
(93203, 'spell_bot_conversion'),
(93204, 'spell_bot_conversion'),
(93205, 'spell_bot_conversion');

UPDATE `spell_target_position` SET `target_orientation`=3.40 WHERE `id`=81611 AND `effIndex`=0;
UPDATE `spell_target_position` SET `target_orientation`=5.96 WHERE `id`=81618 AND `effIndex`=0;
UPDATE `creature_template` SET `faction`=16 WHERE `entry`=43622;

DELETE FROM `spell_script_names` WHERE `spell_id` = '81628';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(81628, 'spell_bot_summon_corrupted_adherent');

UPDATE `creature_template` SET `mechanic_immune_mask`=617299967, `ScriptName`='npc_bot_corrupting_adherent' WHERE `entry`=43622;
UPDATE `creature_template` SET `minlevel`=88, `maxlevel`=88, `exp`=3, `faction`=16, `ScriptName`='npc_bot_blood_old_god' WHERE `entry`=43707;
UPDATE `creature_template` SET `minlevel`=88, `maxlevel`=88, `exp`=3, `faction`=14, `ScriptName`='npc_bot_darkened_creation' WHERE `entry`=44045;
UPDATE `creature_template` SET `ScriptName`='npc_bot_malformation_chogall' WHERE `entry`=43888;

DELETE FROM `spell_script_names` WHERE `spell_id` IN (81831, 81943, 82363, 81761, 82919, 81689, 81713, 82411);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(81831, 'spell_bot_corruption_sickness'),
(81943, 'spell_bot_corruption_accelerated'),
(82363, 'spell_bot_corruption_old_god'),
(81761, 'spell_bot_spilled_blood_of_the_old_god'),
(82919, 'spell_bot_sprayed_corruption'),
(81689, 'spell_corrupting_crash'),
(81713, 'spell_bot_depravity'),
(82411, 'spell_bot_debilitating_beam');

DELETE FROM `conditions` WHERE `SourceEntry` = '91331';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 7, 91331, 0, 0, 31, 0, 3, 43324, 0, 0, 0, '', 'Targeting -> Chogall');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (91331, 93206, 93207, 93208);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(91331, 'spell_bot_twisted_devotion'),
(93206, 'spell_bot_twisted_devotion'),
(93207, 'spell_bot_twisted_devotion'),
(93208, 'spell_bot_twisted_devotion');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (91317, 93365, 93366, 93367);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(91317, 'spell_bot_worshipping'),
(93365, 'spell_bot_worshipping'),
(93366, 'spell_bot_worshipping'),
(93367, 'spell_bot_worshipping');

UPDATE `spell_target_position` SET `target_position_x`=-1092.60, `target_position_y`=-798.77, `target_position_z`=840.41 WHERE `id`=81611 AND `effIndex`=0;
UPDATE `spell_target_position` SET `target_position_x`=-1233.114, `target_position_y`=-799.028, `target_position_z`=836.842 WHERE `id`=81618 AND `effIndex`=0;

DELETE FROM `spell_script_names` WHERE `spell_id` = '82299';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(82299, 'spell_bot_fester_blood');

DELETE FROM `conditions` WHERE `SourceEntry` = '82299';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 7, 82299, 0, 0, 31, 0, 3, 43622, 0, 0, 0, '', 'Targeting -> Adherent');

DELETE FROM `creature_template_addon` WHERE `entry` = '43888';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(43888, '82167');

UPDATE `gameobject_template` SET `flags`=40 WHERE `entry`=205898;

DELETE FROM `conditions` WHERE `SourceEntry` = '82630';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 7, 82630, 0, 0, 31, 0, 3, 43622, 0, 0, 0, '', 'Targeting -> Adherent');

DELETE FROM `conditions` WHERE `SourceEntry` = '82659';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 7, 82659, 0, 0, 31, 0, 3, 43622, 0, 0, 0, '', 'Targeting -> Adherent');

DELETE FROM `conditions` WHERE `SourceEntry` = '82356';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 7, 82356, 0, 0, 31, 0, 3, 43622, 0, 0, 0, '', 'Targeting -> Adherent');

DELETE FROM `spell_script_names` WHERE `spell_id` = '82659';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(82659, 'spell_bot_consume_blood');

UPDATE `creature_template` SET `minlevel`=87, `maxlevel`=87, `exp`=3, `faction`=35, `scale`=2 WHERE `entry` IN (47017, 47016);
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=44045;

DELETE FROM `disables` WHERE `sourceType` = '7' AND `entry` = '671';
INSERT INTO `disables` (`sourceType`, `entry`, `flags`, `params_0`, `params_1`, `comment`) VALUES
(7, 671, 0, '', '', 'MMAP - The Bastion of Twilight');

UPDATE `creature_template` SET `faction`=14, `unit_class`=8 WHERE `entry` IN (45676,45699,45700,45687,50193,50200,50202,50201);
UPDATE `creature_template` SET `minlevel`=87, `maxlevel`=87, `exp`=3, `faction`=14 WHERE `entry` IN (45703, 45721);
UPDATE `creature_template` SET `minlevel`=87, `maxlevel`=87, `exp`=3, `faction`=14 WHERE `entry`=45721;

DELETE FROM `creature_template_addon` WHERE `entry` = '45721';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(45721, '85470, 85290');

UPDATE `creature_template` SET `unit_flags`=33554436 WHERE `entry`=45721;