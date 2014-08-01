UPDATE `creature_template` SET `npcflag`=1, `ScriptName`='npc_first_wyvern' WHERE `entry`=45005;
UPDATE `vehicle_template_accessory` SET `seat_id`=0 WHERE `entry`=45024 AND `seat_id`=1;
UPDATE `vehicle_template_accessory` SET `summontype`=8, `summontimer`=0 WHERE `entry`=45024 AND `seat_id`=0;

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '45024';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(45024, 45028, 0, 1, 'Aggra on Wyvern', 8, 0);
