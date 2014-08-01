UPDATE `creature_template` SET `scriptname`= 'npc_gb_ground_siege_dummy' WHERE `entry`= 40030;
UPDATE `creature_template` SET `difficulty_entry_1`= 48350 WHERE `entry`= 39984;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `exp`= 3, `faction_A`= 14, `faction_H`= 14, `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 12 WHERE `entry`= 48350;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `exp`= 3, `faction_A`= 14, `faction_H`= 14, `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 9 WHERE `entry`= 48348;

UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `exp`= 3, `faction_A`= 14, `faction_H`= 14, `rank`= 3, `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 35, `flags_extra`= 1, `mingold`= 19000, `maxgold`=20000 WHERE `entry`= 48337;
UPDATE `creature_template` SET `mechanic_immune_mask`= 667893759 WHERE `entry` IN (39625, 48337);
