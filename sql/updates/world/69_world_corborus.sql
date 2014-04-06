
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (92111);

INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES

('92111', '92112', '0', 'Random Aggro Taunt - Taunt');

UPDATE `creature_template` SET `mingold`= 18500, `maxgold`= 19000, `minlevel`= 84, `maxlevel`= 84 WHERE `entry`= 43438;
UPDATE `creature_template` SET `mingold`= 18500, `maxgold`= 19000, `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16, `exp`= 3, `unit_flags`= 33088 WHERE `entry`= 49642;

UPDATE `creature_template` SET `exp`= 3, `minlevel`= 82, `maxlevel`= 82, `faction_A`= 16, `faction_H`= 16, `scriptname`= 'npc_tsc_rock_borer' WHERE `entry`= 43917;
UPDATE `creature_template` SET `exp`= 3, `minlevel`= 85, `maxlevel`= 85, `faction_A`= 16, `faction_H`= 16 WHERE `entry`= 49656;
