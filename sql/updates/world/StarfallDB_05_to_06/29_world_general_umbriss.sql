
-- Drake event in Grim Batol
UPDATE `creature_template` SET `scriptname`= 'npc_gb_flying_drake' WHERE `entry` IN(48523, 39390);
UPDATE `creature_template` SET `InhabitType`= 7, `iconname` = 'vehichleCursor', `unit_flags` = 2, `scriptname` = 'npc_battered_red_drake_event', `mechanic_immune_mask` = `mechanic_immune_mask` &~ 64 WHERE `entry`=39294;
UPDATE `creature_template` SET `unit_flags`= (512 + 4 + 131072), `scriptname` = 'npc_gb_net' WHERE `entry` = 42570;

DELETE FROM npc_spellclick_spells WHERE npc_entry = 39294;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
('39294', '80343', '1');

UPDATE `creature_template` SET `scriptname`= 'boss_general_umbriss' WHERE `entry`= 39625;

DELETE FROM `creature_text` WHERE `entry`= 39625;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(39625, 0, 0, 'Cover the rear! Alexstraza\'s brood decimate our rank!', 14, 0, 100, 0, 0, 18537, 'General Umbriss'),
(39625, 0, 1, 'Reinforce the front! We are being invaded!', 14, 0, 100, 0, 0, 18536, 'General Umbriss'),
(39625, 1, 0, 'A million more await my orders. What chance you do have?', 14, 0, 100, 0, 0, 18530, 'General Umbriss'),
(39625, 2, 0, 'Attack you cowardly vermin!', 14, 0, 100, 0, 0, 18535, 'General Umbriss'),
(39625, 3, 0, 'Messy...', 14, 0, 100, 0, 0, 18532, 'General Umbriss'),
(39625, 3, 1, 'Vermin, your dinner awaits!', 14, 0, 100, 0, 0, 18531, 'General Umbriss'),
(39625, 4, 0, '|TInterface\\Icons\\ability_warrior_charge.blp:20|tGeneral Umbriss sets his eyes on |cFFFF0000$N|r and begins to cast |cFFFF0000|Hspell:74670|h[Blitz]|h|r!', 41, 0, 100, 0, 0, 0, 'General Umbriss'),
(39625, 5, 0, '|TInterface\\Icons\\spell_nature_earthquake.blp:20|tGeneral Umbriss begins to cast |cFFFF0000|Hspell:74634|h[Ground Siege]|h|r!', 41, 0, 100, 0, 0, 0, 'General Umbriss to Bodenbelagerung'),
(39625, 6, 0, '%s goes into a frenzy!', 41, 0, 100, 0, 0, 0, 'General Umbriss');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(74668, 'spell_gb_blitz'),
(74669, 'spell_gb_blitz_summon'),
(74639, 'spell_gb_siege_summon');

DELETE FROM conditions WHERE SourceEntry IN (74670, 90250, 74634, 90249);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 1, 74670, 0, 0, 31, 0, 3, 40040, 0, 0, 0, '', 'Blitz - Target Blitz Dummy'),
(13, 1, 90250, 0, 0, 31, 0, 3, 40040, 0, 0, 0, '', 'Blitz - Target Blitz Dummy'),
(13, 1, 74634, 0, 0, 31, 0, 3, 40030, 0, 0, 0, '', 'Ground Siege - Target Siege Dummy'),
(13, 1, 90249, 0, 0, 31, 0, 3, 40030, 0, 0, 0, '', 'Ground Siege - Target Siege Dummy');
