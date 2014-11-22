-- Position update for Andruk (id: 11901) in zone: 331, area: 2897
UPDATE `creature` SET `position_x` = 3352.053, `position_y` = 1051.886, `position_z` = 3.084, `orientation`= 5.308 WHERE `guid` = 176715;

-- Position update for Vhulgra (id: 12616) in zone: 331, area: 431
UPDATE `creature` SET `position_x` = 2303.610, `position_y` = -2523.528, `position_z` = 104.501, `orientation`= 4.862 WHERE `guid` = 176753;

-- Deletes creature Dyslix Silvergrub (id: 40358, guid: 154348) in zone: 15, area: 4010
DELETE FROM `creature` WHERE `guid` = 154348; DELETE FROM creature_addon WHERE guid = 154348;

UPDATE `gossip_menu_option` SET `option_id`=4, `npc_option_npcflag`=8192 WHERE `option_text` LIKE '%Show me where I can fly%';
UPDATE `creature_template` SET `npcflag`=8192 WHERE `entry` IN (37005, 43073);