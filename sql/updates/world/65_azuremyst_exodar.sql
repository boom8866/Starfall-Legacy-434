UPDATE `creature` SET `position_x`=-3865.20, `position_y`=-11641.679, `position_z`=-137.64, `orientation`=2.31 WHERE `guid`=63164;
UPDATE `creature_template` SET `InhabitType`=3 WHERE `entry` IN (17202, 17203);
UPDATE `creature_template` SET `ScriptName`='npc_geezle' WHERE `entry`=17318;

-- No addons present
DELETE FROM `creature` WHERE `id` = '17318';