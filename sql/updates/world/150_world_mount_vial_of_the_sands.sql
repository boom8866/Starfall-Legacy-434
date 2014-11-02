DELETE FROM `item_loot_template` WHERE (`entry`='64657');
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(64657, 67540, 100),
(64657, 67538, 5);

UPDATE creature_template SET vehicleid = '156', npcflag = '16777216' WHERE entry = '50269';
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '50269';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(50269, 80343, 1);