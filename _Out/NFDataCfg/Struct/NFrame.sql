CREATE TABLE IF NOT EXISTS Buff  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS Clan  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS ClanConfig  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS ConsumeData  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS DescData  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS EffectData  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS Equip  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS GM  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS InitProperty  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS Item  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS Language  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS Map  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS NPC  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS NoSqlServer  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS Player  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS Scene  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS Security  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS Server  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS Shop  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS Skill  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS SqlServer  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS Talent  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS Task  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
CREATE TABLE IF NOT EXISTS Team  ( `ID` varchar(128) NOT NULL, PRIMARY KEY (`ID`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8; 

ALTER TABLE `Buff` ADD `DownSaveType` bigint(11) DEFAULT '0' COMMENT '下线是否保存';
ALTER TABLE `Buff` ADD `EffectClearOnDead` bigint(11) DEFAULT '0' COMMENT '死亡是否清除';
ALTER TABLE `Buff` ADD `EffectTimeInterval` double DEFAULT '0.0' COMMENT '每次间隔时间0.5f倍数';
ALTER TABLE `Buff` ADD `EffectTimeValue` bigint(11) DEFAULT '0' COMMENT '总共产生几次';
ALTER TABLE `Buff` ADD `EffectType` bigint(11) DEFAULT '0' COMMENT '影响属性类型(效果类型)  生命，法力(可组合,叠加)';
ALTER TABLE `Buff` ADD `EffectValueReferType` bigint(11) DEFAULT '0' COMMENT '影响值参考类型';
ALTER TABLE `Buff` ADD `EffectValueType` bigint(11) DEFAULT '0' COMMENT '影响值类型 百分比 绝对值--如果是控制属性开关，则只能是绝对值';
ALTER TABLE `Buff` ADD `ReverseReferType` bigint(11) DEFAULT '0' COMMENT '是否还原，不还原的在计算的时候不能保存在runTimeInfo,只能累计在最终值内';
ALTER TABLE `Buff` ADD `WashGroupID` bigint(11) DEFAULT '0' COMMENT '每次间隔时间0.5f倍数';
ALTER TABLE `Clan` ADD `Clan_AD` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '工会公告';
ALTER TABLE `Clan` ADD `Clan_CreateTime` bigint(11) DEFAULT '0' COMMENT '公会创建时间';
ALTER TABLE `Clan` ADD `Clan_Desc` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '工会描述';
ALTER TABLE `Clan` ADD `Clan_Exp` bigint(11) DEFAULT '0' COMMENT '公会经验';
ALTER TABLE `Clan` ADD `Clan_Gold` bigint(11) DEFAULT '0' COMMENT '工会财富';
ALTER TABLE `Clan` ADD `Clan_Honor` bigint(11) DEFAULT '0' COMMENT '公会荣誉';
ALTER TABLE `Clan` ADD `Clan_Icon` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '公会头像';
ALTER TABLE `Clan` ADD `Clan_Level` bigint(11) DEFAULT '0' COMMENT '工会等级';
ALTER TABLE `Clan` ADD `Clan_MemeberCount` bigint(11) DEFAULT '0' COMMENT '成员数量(增加个字段，不然遍历Record太麻烦)';
ALTER TABLE `Clan` ADD `Clan_MemeberMaxCount` bigint(11) DEFAULT '0' COMMENT '成员最大数量';
ALTER TABLE `Clan` ADD `Clan_Name` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '工会名';
ALTER TABLE `Clan` ADD `Clan_PresidentID` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT '' COMMENT '会长ID';
ALTER TABLE `Clan` ADD `Clan_PresidentName` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '会长名';
ALTER TABLE `Clan` ADD `Clan_Rank` bigint(11) DEFAULT '0' COMMENT '公会排名';
ALTER TABLE `Clan` ADD `Guild_EctypID` bigint(11) DEFAULT '0' COMMENT '工会副本ID';
ALTER TABLE `Clan` ADD `Clan_AppyList` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Clan` ADD `Clan_Building` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Clan` ADD `Clan_MemberList` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Clan` ADD `Clan_WarList` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `ConsumeData` ADD `Diamond` bigint(11) DEFAULT '0' COMMENT '钻石';
ALTER TABLE `ConsumeData` ADD `EXP` bigint(11) DEFAULT '0' COMMENT '经验获得,如果是怪物，则是掉落经验';
ALTER TABLE `ConsumeData` ADD `Gold` bigint(11) DEFAULT '0' COMMENT '玩家游戏金币';
ALTER TABLE `ConsumeData` ADD `HP` bigint(11) DEFAULT '0' COMMENT '生命值';
ALTER TABLE `ConsumeData` ADD `MP` bigint(11) DEFAULT '0' COMMENT '法力值';
ALTER TABLE `ConsumeData` ADD `SP` bigint(11) DEFAULT '0' COMMENT '体力';
ALTER TABLE `ConsumeData` ADD `VIPEXP` bigint(11) DEFAULT '0' COMMENT 'VIP经验';
ALTER TABLE `IObject` ADD `ConfigID` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Map` ADD `MaxCount` bigint(11) DEFAULT '0' COMMENT '最大入驻公会';
ALTER TABLE `Map` ADD `Station` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `NPC` ADD `AIOwnerID` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT '' COMMENT 'AI';
ALTER TABLE `NPC` ADD `Camp` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT '' COMMENT '阵营';
ALTER TABLE `NPC` ADD `Diamond` bigint(11) DEFAULT '0' COMMENT '钻石';
ALTER TABLE `NPC` ADD `EXP` bigint(11) DEFAULT '0' COMMENT '经验获得,如果是怪物，则是掉落经验';
ALTER TABLE `NPC` ADD `Gold` bigint(11) DEFAULT '0' COMMENT '玩家游戏金币';
ALTER TABLE `NPC` ADD `HP` bigint(11) DEFAULT '0' COMMENT '生命值';
ALTER TABLE `NPC` ADD `Level` bigint(11) DEFAULT '0' COMMENT '';
ALTER TABLE `NPC` ADD `MP` bigint(11) DEFAULT '0' COMMENT '法力值';
ALTER TABLE `NPC` ADD `MasterID` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT '' COMMENT '召唤者，主人';
ALTER TABLE `NPC` ADD `MasterName` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '召唤者，主人';
ALTER TABLE `NPC` ADD `SP` bigint(11) DEFAULT '0' COMMENT '体力';
ALTER TABLE `NPC` ADD `VIPEXP` bigint(11) DEFAULT '0' COMMENT 'VIP经验';
ALTER TABLE `NPC` ADD `Cooldown` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Player` ADD `ATK_PVP` bigint(11) DEFAULT '0' COMMENT 'PVP攻击力';
ALTER TABLE `Player` ADD `Account` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '玩家的帐号';
ALTER TABLE `Player` ADD `Camp` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT '' COMMENT '阵营';
ALTER TABLE `Player` ADD `Commend` bigint(11) DEFAULT '0' COMMENT 'Cup';
ALTER TABLE `Player` ADD `ConnectKey` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '玩家连接服务器的KEY';
ALTER TABLE `Player` ADD `Cup` bigint(11) DEFAULT '0' COMMENT 'Cup';
ALTER TABLE `Player` ADD `DEF_PVP` bigint(11) DEFAULT '0' COMMENT 'PVP防御力';
ALTER TABLE `Player` ADD `Diamond` bigint(11) DEFAULT '0' COMMENT '钻石';
ALTER TABLE `Player` ADD `EXP` bigint(11) DEFAULT '0' COMMENT '经验获得,如果是怪物，则是掉落经验';
ALTER TABLE `Player` ADD `FightHeroCnfID` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '主要是给离线玩家看';
ALTER TABLE `Player` ADD `FightHeroID` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT '' COMMENT 'FightHeroID';
ALTER TABLE `Player` ADD `FirstTarget` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT '' COMMENT '首要目标';
ALTER TABLE `Player` ADD `GMLevel` bigint(11) DEFAULT '0' COMMENT 'GM等级';
ALTER TABLE `Player` ADD `Gold` bigint(11) DEFAULT '0' COMMENT '玩家游戏金币';
ALTER TABLE `Player` ADD `GuildID` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT '' COMMENT '公会ID';
ALTER TABLE `Player` ADD `Head` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT 'headicon--guild';
ALTER TABLE `Player` ADD `HeroCnfID1` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '主要是给离线玩家看';
ALTER TABLE `Player` ADD `HeroCnfID2` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '主要是给离线玩家看';
ALTER TABLE `Player` ADD `HeroCnfID3` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '主要是给离线玩家看';
ALTER TABLE `Player` ADD `HeroID1` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT '' COMMENT 'Hero1';
ALTER TABLE `Player` ADD `HeroID2` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT '' COMMENT 'Hero2';
ALTER TABLE `Player` ADD `HeroID3` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT '' COMMENT 'Hero3';
ALTER TABLE `Player` ADD `HeroStar1` bigint(11) DEFAULT '0' COMMENT '主要是给离线玩家看';
ALTER TABLE `Player` ADD `HeroStar2` bigint(11) DEFAULT '0' COMMENT '主要是给离线玩家看';
ALTER TABLE `Player` ADD `HeroStar3` bigint(11) DEFAULT '0' COMMENT '主要是给离线玩家看';
ALTER TABLE `Player` ADD `HomeCellPos` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT '' COMMENT '玩家下线的时候需要保存上次在线的场景';
ALTER TABLE `Player` ADD `HomeSceneID` bigint(11) DEFAULT '0' COMMENT '玩家下线的时候需要保存上次在线的场景';
ALTER TABLE `Player` ADD `Item1` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT 'Skill4';
ALTER TABLE `Player` ADD `Item1Count` bigint(11) DEFAULT '0' COMMENT 'Item1Count';
ALTER TABLE `Player` ADD `Item2` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT 'Skill5';
ALTER TABLE `Player` ADD `Item2Count` bigint(11) DEFAULT '0' COMMENT 'Item2Count';
ALTER TABLE `Player` ADD `Item3` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT 'Skill5';
ALTER TABLE `Player` ADD `Item3Count` bigint(11) DEFAULT '0' COMMENT 'Item3Count';
ALTER TABLE `Player` ADD `Job` bigint(11) DEFAULT '0' COMMENT '职业';
ALTER TABLE `Player` ADD `LastOfflineTime` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT '' COMMENT '上次下线时间';
ALTER TABLE `Player` ADD `Level` bigint(11) DEFAULT '0' COMMENT '等级';
ALTER TABLE `Player` ADD `MAXEXP` bigint(11) DEFAULT '0' COMMENT '升级需要的经验';
ALTER TABLE `Player` ADD `MatchStar` bigint(11) DEFAULT '0' COMMENT '';
ALTER TABLE `Player` ADD `Name` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '角色名';
ALTER TABLE `Player` ADD `OnlineCount` bigint(11) DEFAULT '0' COMMENT '上线次数';
ALTER TABLE `Player` ADD `OnlineTime` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT '' COMMENT '本次上线时间';
ALTER TABLE `Player` ADD `PrefabPath` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '预设路径';
ALTER TABLE `Player` ADD `RELIVE_SOUL` bigint(11) DEFAULT '0' COMMENT '转生次数';
ALTER TABLE `Player` ADD `Race` bigint(11) DEFAULT '0' COMMENT '种族';
ALTER TABLE `Player` ADD `Report` bigint(11) DEFAULT '0' COMMENT 'Cup';
ALTER TABLE `Player` ADD `Sex` bigint(11) DEFAULT '0' COMMENT '性别';
ALTER TABLE `Player` ADD `ShowName` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '显示的名字';
ALTER TABLE `Player` ADD `Skill1` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT 'Skill1';
ALTER TABLE `Player` ADD `Skill2` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT 'Skill2';
ALTER TABLE `Player` ADD `Skill3` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT 'Skill3';
ALTER TABLE `Player` ADD `Streak` bigint(11) DEFAULT '0' COMMENT 'streak win count';
ALTER TABLE `Player` ADD `TeamID` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT '' COMMENT '所在队伍ID';
ALTER TABLE `Player` ADD `TotalLineTime` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT '' COMMENT '今日在线时长{截至至本次上线时间}';
ALTER TABLE `Player` ADD `TotalTime` bigint(11) DEFAULT '0' COMMENT '在线时间';
ALTER TABLE `Player` ADD `VIPEXP` bigint(11) DEFAULT '0' COMMENT 'VIP经验';
ALTER TABLE `Player` ADD `VIPLevel` bigint(11) DEFAULT '0' COMMENT '经验获得,如果是怪物，则是掉落经验';
ALTER TABLE `Player` ADD `BagEquipList` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Player` ADD `BagItemList` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Player` ADD `BuildingList` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Player` ADD `BuildingListProduce` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Player` ADD `Clan_AppyList` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Player` ADD `Clan_Building` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Player` ADD `Clan_MemberList` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Player` ADD `Clan_WarList` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Player` ADD `Cooldown` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Player` ADD `HeroValue` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Player` ADD `PlayerHero` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Player` ADD `TaskList` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Player` ADD `WarList` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Shop` ADD `Count` bigint(11) DEFAULT '0' COMMENT '';
ALTER TABLE `Shop` ADD `Diamond` bigint(11) DEFAULT '0' COMMENT '';
ALTER TABLE `Shop` ADD `Gold` bigint(11) DEFAULT '0' COMMENT '';
ALTER TABLE `Shop` ADD `ItemID` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Shop` ADD `Level` bigint(11) DEFAULT '0' COMMENT '';
ALTER TABLE `Shop` ADD `Steel` bigint(11) DEFAULT '0' COMMENT '';
ALTER TABLE `Shop` ADD `Stone` bigint(11) DEFAULT '0' COMMENT '';
ALTER TABLE `Shop` ADD `Type` bigint(11) DEFAULT '0' COMMENT '';
ALTER TABLE `Team` ADD `Captain` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT '' COMMENT '队长ID';
ALTER TABLE `Team` ADD `PresidentName` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '会长名';
ALTER TABLE `Team` ADD `ApplyList` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';
ALTER TABLE `Team` ADD `MemberList` text COLLATE utf8mb4_unicode_ci  DEFAULT '' COMMENT '';