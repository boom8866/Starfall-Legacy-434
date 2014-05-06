
-- Fix Groth Deathblow Vendor Option
UPDATE `creature_template` SET `gossip_menu_id`= 12607 WHERE `entry`= 49387;
UPDATE `gossip_menu_option` SET `option_id`= 3, `npc_option_npcflag`= 128  WHERE `menu_id`= 12607  AND `id`= 0;

-- Delete some wrong equipments
DELETE FROM `creature_equip_template` WHERE `entry` IN (1109, 462);

-- Make Wanted: Hogger Poster selectable
UPDATE `gameobject_template` SET `flags`= 0 WHERE `entry`= 156561;

-- Set respawn time for the homeless stormwind citizens to 1 minute
UPDATE `creature` SET `spawntimesecs`= 60 WHERE `id`= 42384;
