DELETE FROM `gameobject` WHERE `guid` IN (180001, 180002, 180003, 180004, 180005, 180029);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`) VALUES 
(180001, 250001, 169, 0, 0, 1, 1, 1433.08, -3492.67, -20.9978, 5.38861, -0, -0, -0.432522, 0.901623, 300, 255, 1, '', NULL),
(180002, 250001, 169, 0, 0, 1, 1, 1450.51, -3480.24, -20.9993, 4.73280, -0, -0, -0.699854, 0.714286, 300, 255, 1, '', NULL),
(180003, 250001, 169, 0, 0, 1, 1, 1466.24, -3479.19, -20.9993, 4.12804, -0, -0, -0.880810, 0.473470, 300, 255, 1, '', NULL),
(180004, 250001, 169, 0, 0, 1, 1, 1480.78, -3489.96, -20.9993, 3.64502, -0, -0, -0.968488, 0.249062, 300, 255, 1, '', NULL),
(180005, 250001, 169, 0, 0, 1, 1, 1485.99, -3502.24, -20.9993, 3.35835, -0, -0, -0.994133, 0.108164, 300, 255, 1, '', NULL),
(180029, 250006, 169, 0, 0, 1, 1, 1462.27, -3453.42, -21, 4.70844, -0, -0, -0.708501, 0.70571, 300, 255, 1, '', NULL);

DELETE FROM `gameobject_template` WHERE `entry` IN (250001, 250006);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES 
(250001, 1, 5, 'Drakkari Tablets', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 'go_drakkari_tablets', 12340),
(250006, 0, 9214, 'Icewall', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340);

DELETE FROM `instance_template` WHERE `map`=169;
INSERT INTO `instance_template` (`map`, `parent`, `script`, `allowMount`) VALUES 
(169, 0, 'instance_test_lair', 0);

DELETE FROM `creature_template` WHERE `entry`=90016;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES 
(90016, 0, 0, 0, 0, 0, 1126, 23501, 0, 0, 'Low Poly Fire', '', '', 0, 1, 1, 2, 35, 0, 1, 1.14286, 1, 0, 0, 2000, 2000, 1, 1, 1, 33555200, 2048, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 128, '', 12340);
