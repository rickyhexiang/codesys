# 使用说明

GLODON.IOT.SDK 是面向开发者的协议工具开发包，使用它可以快速与广联达云平台建立联接

## 参考文档

- [硬件开发指南](../../../doc/hardware-dev-guide.md)

- [快速开始](../../../doc/get-started.md)

- [在线文档](https://zl.glodon.com/docs/guide/app-dev-guide.html)

## SDK的信息

- SDK版本号: version.1.4

- 设备模型信息

  * 模型规则版本: 1.0.0

  * 模型ID: cfb10bfb-4b85-4a29-992c-946ebb2bd105

  * 模型Json

    ```json
    {
    "imageUrl": "http://private-iot-glodon.oss-cn-beijing.aliyuncs.com/system/model.png", 
    "description": "必定成功", 
    "updatedTime": 1514878929431, 
    "deleted": false, 
    "attributesMap": {
        "startTask": {
            "code": "startTask", 
            "description": "", 
            "dataType": "String", 
            "readable": "R", 
            "channel": "m", 
            "name": "开始加工任务"
        }, 
        "endTask": {
            "code": "endTask", 
            "description": "", 
            "dataType": "String", 
            "readable": "R", 
            "channel": "m", 
            "name": "结束加工任务"
        }, 
        "updateTask": {
            "code": "updateTask", 
            "description": "", 
            "dataType": "String", 
            "readable": "R", 
            "channel": "m", 
            "name": "更新加工任务"
        }, 
        "warningInfo": {
            "code": "warningInfo", 
            "description": "", 
            "dataType": "String", 
            "readable": "R", 
            "channel": "m", 
            "name": "报警信息"
        }, 
        "electricFlow": {
            "code": "electricFlow", 
            "description": "", 
            "dataType": "Float", 
            "readable": "R", 
            "channel": "m", 
            "name": "设备电流"
        }, 
        "machineState": {
            "code": "machineState", 
            "description": "", 
            "dataType": "String", 
            "readable": "R", 
            "channel": "m", 
            "name": "更新设备状态"
        }
    }, 
    "name": "弯箍机", 
    "actionsMap": {
        "curTaskData": {
            "paramsMap": {
                "taskInfo": {
                    "required": true, 
                    "code": "taskInfo", 
                    "type": "String", 
                    "description": "", 
                    "name": "任务信息"
                }
            }, 
            "code": "curTaskData", 
            "description": "", 
            "name": "任务信息"
        }, 
        "curTaskCount": {
            "paramsMap": {
                "count": {
                    "required": true, 
                    "code": "count", 
                    "type": "Integer", 
                    "description": "", 
                    "name": "数量"
                }
            }, 
            "code": "curTaskCount", 
            "description": "", 
            "name": "当前任务数量"
        }
    }, 
    "deviceType": "SteelMachine", 
    "createdBy": "yujun@zhongran.com", 
    "updatedBy": "yujun@zhongran.com", 
    "createdTime": 1507616468129, 
    "tenantId": "cb0b1bfc-b96e-4e01-82af-42afca93ffdb", 
    "id": "cfb10bfb-4b85-4a29-992c-946ebb2bd105", 
    "metadata": {}
}
    ```

## 筑联

   广联达旗下品牌 [https://zl.glodon.com](https://zl.glodon.com)

