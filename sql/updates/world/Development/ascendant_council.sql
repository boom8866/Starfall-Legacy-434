/*
034935.000 -- aegis
045000.000
*/

REPLACE INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6625, 'at_ascendant_council_1'),
(6626, 'at_ascendant_council_2'),
(6627, 'at_ascendant_council_3');


UPDATE `creature_template` SET `scriptname`= 'npc_ascendant_council_controller' WHERE `entry`= 43691;
UPDATE `creature_template` SET `scriptname`= 'boss_feludius' WHERE `entry`= 43687;
UPDATE `creature_template` SET `scriptname`= 'boss_ignacious' WHERE `entry`= 43686;
UPDATE `creature_template` SET `scriptname`= 'boss_arion' WHERE `entry`= 43688;
UPDATE `creature_template` SET `scriptname`= 'boss_terrastra' WHERE `entry`= 43689;

-- Water Bomb
UPDATE `creature_template` SET `minlevel`= 80, `maxlevel`= 80, `faction`= 14, `unit_flags`= 33554432, `flags_extra`= 128, `InhabitType`= 4 WHERE `entry`= 44201;
-- Inferno Rush
UPDATE `creature_template` SET `minlevel`= 80, `maxlevel`= 80, `faction`= 14, `unit_flags`= 33554432, `flags_extra`= 128, `InhabitType`= 4 WHERE `entry`= 47501;

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(43324, 4, 0, 'Welcome, mortals. (Frail little children). Few have laid eyes on this inner sanctum. (They reach out to touch the fire!)', 14, 0, 100, 0, 0, 22065, 'Cho''gall - Ascendant Countil Intro'),
(43324, 5, 0, 'It is here the chosen realize their destiny. (One with eternity). And it is here that you will realize yours.(End of the flesh. End of the flesh)!', 14, 0, 100, 0, 0, 22066, 'Cho''gall - Ascendant Countil Intro'),
(43324, 6, 0, 'Brothers of Twilight! The Hammer calls to you! (Fire water earth air). Leave your mortal shell behind. (Fire water earth air). Embrace your new forms for here and everafter! (Burn and drown and crush and suffocate). And use your gifts to destroy the unbelievers. (Burn and drown and crush and suffocate)!!', 14, 0, 100, 0, 0, 22067, 'Cho''gall - Ascendant Countil Intro'),
-- Feludius
(43687, 0, 0, 'You dare invade our lord''s sanctum?', 14, 0, 100, 0, 0, 20162, 'Feludius - Aggro'),
(43687, 1, 0, 'Perish!', 14, 0, 100, 0, 0, 20163, 'Feludius - Slay'),
(43687, 2, 0, 'I will freeze the blood in your veins!', 14, 0, 100, 0, 0, 20164, 'Feludius - Glaciate Say'),
(43687, 3, 0, '%s begins to cast Glaciate!', 41, 0, 100, 0, 0, 0, 'Feludius - Glaciate Accounce'),
-- Ignacious
(43686, 0, 0, 'You will die for your insolence!', 14, 0, 100, 0, 0, 20285, 'Ignacious - Aggro'),
(43686, 1, 0, 'More fuel for the fire!', 14, 0, 100, 0, 0, 20286, 'Ignacious - Slay'),
(43686, 2, 0, 'BURN!', 14, 0, 100, 0, 0, 20287, 'Ignacious - Rising Flames Say'),
(43686, 3, 0, '%s begins to cast Rising Flames!', 41, 0, 100, 0, 0, 0, 'Ignacious - Rising Flames Accounce'),
-- Arion
(43688, 0, 0, 'Enough of this foolishness!', 14, 0, 100, 0, 0, 20237, 'Arion - Aggro'),
(43688, 1, 0, 'Merely a whisper in the wind....', 14, 0, 100, 0, 0, 20238, 'Arion - Slay'),
(43688, 2, 0, 'Wind, hear my call!', 14, 0, 100, 0, 0, 20239, 'Arion - Call Winds'),
(43688, 3, 0, '%s begins to cast Thundershock!', 41, 0, 100, 0, 0, 0, 'Arion - Thundershock Accounce'),
-- Terrastra
(43689, 0, 0, 'We will handle them!', 14, 0, 100, 0, 0, 21843, 'Terrastra - Aggro'),
(43689, 1, 0, 'The soil welcomes your bones!', 14, 0, 100, 0, 0, 21842, 'Terrastra - Slay'),
(43689, 2, 0, 'The earth will devour you!', 14, 0, 100, 0, 0, 21844, 'Terrastra - Ground Rupture'),
(43689, 3, 0, '%s begins to cast Quake!', 41, 0, 100, 0, 0, 0, 'Terrastra - Quake Accounce'),
-- Ascendant Council Controller
(43691, 0, 0, 'The ground beneath you rumbles ominously...', 41, 0, 100, 0, 0, 0, 'Ascendant Council Controller - Quake'),
(43691, 1, 0, 'The air around you crackles with energy...', 41, 0, 100, 0, 0, 0, 'Ascendant Council Controller - Thundershock');

REPLACE INTO `spell_script_names` (`spell_id`, `scriptname`) VALUES
(82699, 'spell_ac_water_bomb'),
(82746, 'spell_ac_glaciate'),
(92506, 'spell_ac_glaciate'),
(92507, 'spell_ac_glaciate'),
(92508, 'spell_ac_glaciate'),
(82665, 'spell_ac_heart_of_ice'),
(82860, 'spell_ac_inferno_rush_fire'),
(92523, 'spell_ac_inferno_rush_fire'),
(92524, 'spell_ac_inferno_rush_fire'),
(92525, 'spell_ac_inferno_rush_fire'),
(82660, 'spell_ac_burning_blood');


DELETE FROM `conditions` WHERE `SourceEntry` IN (82699);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 82699, 0, 0, 31, 0, 3, 44201, 0, 0, 0, '', 'Water Bomb - Target Water Bomb');


UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 779687;
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 779702;
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 779704;
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 779703;
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 779705;
DELETE FROM `creature` WHERE `id` IN (44201, 50297);
