UPDATE `creature_template` SET `minlevel`= 86, `maxlevel`= 86, `rank`= 3, `speed_walk`= 2,  `speed_run`= 1.64286, `scriptname`= 'boss_forgemaster_throngus', `mechanic_immune_mask`= 667893759 WHERE `entry`= 40177;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `rank`= 3, `faction_A`= 1771, `faction_H`= 1771, `speed_walk`= 2, `speed_run`= 1.64286, `exp`= 3, `mechanic_immune_mask`= 667893759 WHERE `entry`= 48702;
UPDATE `creature_template` SET `unit_flags`= 64, `unit_flags2`= 67584 WHERE `entry`IN (40177, 48702);

UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 7, `faction_H`= 7, `unit_flags`= 34078720, `flags_extra`= 131, `scriptname`= 'npc_gb_cave_in' WHERE `entry`= 40228;
UPDATE `creature_template` SET `flags_extra`= 131, `scriptname`= 'npc_gb_fixate_trigger'  WHERE `entry`= 40255;
UPDATE `creature_template` SET `unit_flags`= 33554432 WHERE `entry`= 40197;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 7, `faction_H`= 7, `unit_flags`= 33554432, `flags_extra`= 131, `scriptname`= 'npc_gb_fire_patch' WHERE `entry`= 48711;

DELETE FROM `creature` WHERE `id`= 40255;

DELETE FROM `creature_text` WHERE `entry`= 40177;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(40177, 0, 0, 'NO! Throngus get whipped again if he no finish', 14, 0, 100, 0, 0, 18943, 'Throngus - Aggro'),
(40177, 1, 0, 'Throngus use your corpse on body. Somewhere...', 14, 0, 100, 0, 0, 18944, 'Throngus - Slay 1'),
(40177, 1, 1, 'You break easy!', 14, 0, 100, 0, 0, 18944, 'Throngus - Slay 2'),
(40177, 2, 0, '|TInterface\\Icons\\inv_shield_76.blp:20|t%s equips his |cFFFF0000Shield|r and gains |cFFFF0000|Hspell:74908|h[Personal Phalanx]|h|r!', 41, 0, 100, 0, 0, 0, 'Throngus -Announce Planax'),
(40177, 3, 0, 'You not get through defenses!', 14, 0, 100, 0, 0, 18947, 'Throngus - Phalanx'),
(40177, 4, 0, '|TInterface\\Icons\\inv_mace_15.blp:20|t%s equips his |cFFFF0000Mace|r and is |cFFFF0000|Hspell:75007|h[Encumbered]|h|r!', 41, 0, 100, 53, 0, 0, 'Throngus - Announce Mace'),
(40177, 5, 0, 'Oh, this is gonna HURT!', 14, 0, 100, 53, 0, 18949, 'Throngus - Mace'),
(40177, 6, 0, '|TInterface\\Icons\\ability_dualwield.blp:20|t%s equips his |cFFFF0000Swords|r and gains |cFFFF0000|Hspell:74981|h[Dual Blades]|h|r!', 41, 0, 100, 0, 0, 0, 'Throngus - Announce Dual Blades'),
(40177, 7, 0, 'Throngus SLICE you up!', 14, 0, 100, 0, 0, 18948, 'Throngus - Mace'),
(40177, 8, 0, '$N is impaled!', 41, 0, 100, 0, 0, 0, 'Throngus - Announce Slam'),
(40177, 9, 0, 'Death... Good choice. Not best choice maybe, but better than fail and live.', 14, 0, 100, 0, 0, 18946, 'Throngus Death');

DELETE FROM `conditions` WHERE `SourceEntry` IN (75071, 74945);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 75071, 0, 0, 31, 0, 3, 40255, 0, 0, 0, '', 'Fixate Effect -  Target Fixate Trigger'),
(13, 7, 74945, 0, 0, 31, 0, 3, 40197, 0, 0, 0, '', 'Flame Arrow Barrage - Target Twilight Archer');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(74984, 'spell_gb_mighty_stomp'),
(75000, 'spell_gb_pick_weapon'),
(74914, 'spell_gb_fixate_trigger_aoe'),
(74945, 'spell_gb_flame_arrows_aoe'),
(74944, 'spell_gb_flame_arrows'),
(90810, 'spell_gb_flame_arrows'),
(74981, 'spell_gb_dual_blades'),
(90738, 'spell_gb_dual_blades'),
(74976, 'spell_gb_disorienting_roar'),
(90737, 'spell_gb_disorienting_roar'),
(75007, 'spell_gb_encumbered'),
(90729, 'spell_gb_encumbered');
