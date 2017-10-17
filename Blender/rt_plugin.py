import bpy
import os
import jsonpickle
import time
import math
from bpy.props import (BoolProperty)
from bpy.types import (PropertyGroup)

#Classes
class Vert:
    index = 0
    x = 0
    y = 0
    z = 0
    def __init__(self, index, x, y, z):
        self.index = index
        self.x = x
        self.y = y
        self.z = z

class Face:
    verts = []
    def __init__(self, verts):
        self.verts = verts

class MeshObject(object):
    verts = None
    faces = None
    name = None
    def __init__(self, name):
        self.name = name

class CameraObject(object):
    name = None
    near = None
    far = None
    lens = None
    def __init__(self, name):
        self.name = name

class SpotLampObject(object):
    name = None
    intensity = None
    distance = None
    angle = None
    blend = None
    def __init__(self, name):
        self.name = name

class SubDiv():
    subs = 0
    def __init__(self, subs):
        self.subs = subs

class EmptyObject(object):
    name = None
    def __init__(self, name):
        self.name = name

class SceneNode(object):
    childs = []
    name = None
    refType = None
    location = []
    rotation = []
    def __init__(self, name, type):
        self.name = name
        self.refType = type


#TODO add types to nodes and create corresponding .json files

def createReferences(scene):
    root = []
    for o in scene.objects:
        if scene.ignore_hiera:
            check = checkObjectType(scene, o)
            name = o.name
            type = o.type
            if check == 2:
                print("is ignored")
                name = name+"(ignored)"
                type = "IGNORED"
            elif check == 0:
                print("is not suported")
                name = name+"(unsuported)"
                type = "UNSUPORTED"
            else:
                print("is suported")
            node = SceneNode(name, type)
            node.location = [o.location.x] + [o.location.y] +[o.location.z]
            node.rotation = [round(math.degrees(o.rotation_euler.x),3)] + [ round(math.degrees(o.rotation_euler.y),3)] +[ round(math.degrees(o.rotation_euler.z),3)]
            createObjectRef(scene, o, type)
            root = root+[node]
        else:
            #if Object has parents it will be ignored cause it is handled elsewhere
            if o.parent == None:
                check = checkObjectType(scene, o)
                name = o.name
                type = o.type
                if check == 2:
                    print("is ignored")
                    name = name+"(ignored)"
                    type = "IGNORED"
                elif check == 0:
                    print("is not suported")
                    name = name+"(unsuported)"
                    type = "UNSUPORTED"
                else:
                    print("is suported")
                node = SceneNode(name, type)
                node.location = [o.location.x] + [o.location.y] +[o.location.z]
                node.rotation = [round(math.degrees(o.rotation_euler.x),3)] + [ round(math.degrees(o.rotation_euler.y),3)] +[ round(math.degrees(o.rotation_euler.z),3)]
                createObjectRef(scene, o, type)
                createChildNodes(scene, node, o)
                root = root+[node]



    frozen = jsonpickle.encode(root, unpicklable=False)
    print("##########")
    filePath = scene.ref_path + "\\_refRoot.json"
    f = open(bpy.path.abspath(filePath), 'w')
    f.write(frozen)
    f.close()

def createChildNodes(scene, parentNode, object):
    #parentNode.childs = [SceneNode('') for i in range(len(object.children))]
    for child in object.children:
        check = checkObjectType(scene, child)
        name = child.name
        type = child.type
        if check == 2:
            print("child is ignored")
            name = name+"(ignored)"
            type = "IGNORED"
        elif check == 0:
            print("child is not suported")
            name = name+"(unsuported)"
            type = "UNSUPORTED"
        else:
            print("child is suported")
        node = SceneNode(name, type)
        node.location = [child.location.x] + [child.location.y] +[child.location.z]
        node.rotation = [round(math.degrees(child.rotation_euler.x),3)] + [ round(math.degrees(child.rotation_euler.y),3)] +[ round(math.degrees(child.rotation_euler.z),3)]
        parentNode.childs = parentNode.childs + [node]
        createObjectRef(scene, child, type)
        createChildNodes(scene, node, child)


def checkObjectType(scene, object):
    type = object.type
    if type == "MESH":
        if not scene.ignore_geo:
            return 1
        else:
            return 2
    elif type == "CAMERA":
        if not scene.ignore_cam:
            return 1
        else:
            return 2
    elif type == "LAMP" and object.data.type == "SPOT":
        if not scene.ignore_light:
            return 1
        else:
            return 2
    else:
        return 0


def createObjectRef(scene, object, type):
    if type == "MESH":
         createMeshObject(scene, object)
    elif type == "CAMERA":
        createCameraObject(scene, object)
    elif type == "LAMP" and object.data.type == "SPOT":
        createSpotLampObject(scene, object)
    else:
        createEmptyObject(scene, object, type)

def createEmptyObject(scene, object, type):
    myObj = EmptyObject(object.name + "("+type+")")
    frozen = jsonpickle.encode(myObj, unpicklable=False)

    filePath = scene.ref_path + "\\" + object.name + ".json"
    f = open(bpy.path.abspath(filePath), 'w')
    f.write(frozen)
    f.close()

def createMeshObject(scene, object):
    myObj = MeshObject(object.name)
    mesh = object.data

    myObj.verts = [Vert(0,0,0,0) for i in range(len(mesh.vertices))]
    myObj.faces = [Face([]) for i in range(len(mesh.polygons))]

    for idx, vert in enumerate(mesh.vertices):
        myObj.verts[idx] = Vert(idx, vert.co.x, vert.co.y, vert.co.z)

    for idx, face in enumerate(mesh.polygons):
        for vert in face.vertices:
            myObj.faces[idx].verts.append(vert)

    frozen = jsonpickle.encode(myObj, unpicklable=False)

    filePath = scene.ref_path + "\\" + object.name + ".json"
    f = open(bpy.path.abspath(filePath), 'w')
    f.write(frozen)
    f.close()


def createCameraObject(scene, object):
    cam = CameraObject(object.name)
    cam.near = object.data.clip_start
    cam.far = object.data.clip_end
    cam.lens = object.data.angle

    frozen = jsonpickle.encode(cam, unpicklable=False)

    filePath = scene.ref_path + "\\" + object.name + ".json"
    f = open(bpy.path.abspath(filePath), 'w')
    f.write(frozen)
    f.close()

def createSpotLampObject(scene, object):
    lamp = SpotLampObject(object.name)
    lamp.intensity = object.data.energy
    lamp.distance = object.data.distance
    lamp.angle = round(math.degrees(object.data.spot_size),2)
    lamp.blend = object.data.spot_blend

    frozen = jsonpickle.encode(lamp, unpicklable=False)

    filePath = scene.ref_path + "\\" + object.name + ".json"
    f = open(bpy.path.abspath(filePath), 'w')
    f.write(frozen)
    f.close()

def updateHandler(self, context):
    print (context.scene.autoOptions)
    if context.scene.auto_bool:
        if context.scene.autoOptions == "0":
            lastOP = len(bpy.context.window_manager.operators) + 1
            bpy.app.handlers.scene_update_post.append(onUpdate)
            print("On Change handler added")
        else:
            bpy.app.handlers.save_pre.append(onSave)
            print("On Save handler added")
    else:
        bpy.app.handlers.scene_update_post.clear()
        bpy.app.handlers.save_pre.clear()
        print("handler cleared")
    return


def initSceneProperties(scene):

    # bool for auto update
    bpy.types.Scene.auto_bool = BoolProperty(
        name="Auto Update",
        description="Check to automatically update references",
        default = False,
        update = updateHandler
        )

    # Ignore box booleans
    bpy.types.Scene.ignore_geo = BoolProperty(
        name="Geometry",
        description="Check to ignore geometry in references",
        default = False
        )
    bpy.types.Scene.ignore_light = BoolProperty(
        name="Lights",
        description="Check to ignore lights in references",
        default = False
        )
    bpy.types.Scene.ignore_cam = BoolProperty(
        name="Cameras",
        description="Check to ignore cameras in references",
        default = False
        )
    bpy.types.Scene.ignore_mod = BoolProperty(
        name="Modifiers",
        description="Check to ignore modifiers in references",
        default = False
        )
    bpy.types.Scene.ignore_hiera = BoolProperty(
        name="Scene Hierarchy",
        description="Check to ignore hierarchy of objects in references",
        default = False
        )

    # Bool for active Reference
    bpy.types.Scene.refPresent = BoolProperty(
        default=False
        )

    # String for Reference path
    bpy.types.Scene.ref_path = bpy.props.StringProperty (
        name = "Ref Path",
        default = "C:\\Temp\\",
        description = "Define the Reference Path",
        subtype = 'DIR_PATH'
        )

    # Auto update options
    enum_items = (('0','On Change','References will be updated when scene is changed.'),('1','On Save','References will be updated when blend file is saved.'))
    bpy.types.Scene.autoOptions = bpy.props.EnumProperty(name = "", description = "Auto Update Options", items = enum_items, default = "1")

initSceneProperties(bpy.context.scene)

#Custom Panel in tools region
class ToolsPanel(bpy.types.Panel):
    bl_label = "Realtime Referencing"
    bl_space_type = "VIEW_3D"
    bl_region_type = "TOOLS"

    def draw(self, context):
        #Definition and Placement of UI elements
        refRow = self.layout.row()
        refRow.prop(context.scene, 'ref_path')
        self.layout.separator()
        ignoreBox = self.layout.box()
        ignoreBox.label("Ignore:")
        ignoreBox.prop(context.scene, "ignore_geo")
        ignoreBox.prop(context.scene, "ignore_light")
        ignoreBox.prop(context.scene, "ignore_cam")
        ignoreBox.prop(context.scene, "ignore_mod")
        ignoreBox.prop(context.scene, "ignore_hiera")
        createButtonRow = self.layout.row()
        createButtonRow.operator("button.create")
        deleteButtonRow = self.layout.row()
        deleteButtonRow.operator("button.delete")
        self.layout.separator()

        updateCol = self.layout.column()
        updateButtonRow = updateCol.row()
        updateButtonRow.operator("button.update")
        autoUpdateRow = updateCol.row()
        autoBox = autoUpdateRow.box()
        autoBox.prop(context.scene, "auto_bool")
        optionsRow = autoBox.row()
        optionsRow.prop(context.scene, "autoOptions")

        #define enable state
        updateCol.enabled = context.scene.refPresent
        deleteButtonRow.enabled = context.scene.refPresent
        createButtonRow.enabled = not context.scene.refPresent
        ignoreBox.enabled = not context.scene.refPresent
        refRow.enabled = not context.scene.refPresent
        updateButtonRow.enabled = not context.scene.auto_bool
        optionsRow.enabled = not context.scene.auto_bool



#    Update Button
class OBJECT_OT_UpdateButton(bpy.types.Operator):
    bl_idname = "button.update"
    bl_label = "Update"

    def execute(self, context):
        createReferences(context.scene)
        return{'FINISHED'}

#    Create Reference Button
class OBJECT_OT_CreateButton(bpy.types.Operator):
    bl_idname = "button.create"
    bl_label = "Create References"

    def execute(self, context):
        #Check for invalid Ignores
        if context.scene.ignore_geo and context.scene.ignore_light and context.scene.ignore_cam and context.scene.ignore_mod and context.scene.ignore_hiera:
            self.report({'ERROR'}, "At least one option in the 'Ignore:' box needs to be unchecked!")
            return{'CANCELLED'}
        if context.scene.ignore_geo and not context.scene.ignore_mod:
            self.report({'ERROR'}, "Can't reference Modifiers without Geometry Objects!")
            return{'CANCELLED'}

        #Check for invalid Reference Path
        if not os.path.isdir(context.scene.ref_path):
            self.report({'ERROR'}, "Selected Reference Path '%s' does not exist!"%context.scene.ref_path)
            return{'CANCELLED'}

        #Check for empty scene
        if len(context.scene.objects) == 0:
            self.report({'ERROR'}, "No Objects found in Scene")
            return{'CANCELLED'}

        # Enable/Disable UI elements
        context.scene.refPresent = True

        createReferences(context.scene)

        return{'FINISHED'}

#    Delete Reference Button
class OBJECT_OT_DeleteButton(bpy.types.Operator):
    bl_idname = "button.delete"
    bl_label = "Delete References"

    def execute(self, context):
        context.scene.refPresent = False

        return{'FINISHED'}



#
#	Registration
#   All panels and operators must be registered with Blender; otherwise
#   they do not show up. The simplest way to register everything in the
#   file is with a call to bpy.utils.register_module(__name__).
#

bpy.utils.register_module(__name__)


lastOP = len(bpy.context.window_manager.operators) + 1
curOP = lastOP

# OBJECT CHANGE LISTENER!!!!
def onUpdate(scene):
    #print("now")
    global lastOP
    global curOP
    updated_objects = []

    curOP = len(bpy.context.window_manager.operators)
    #TODO
    #need to check if value changed from last update via bpy.context.window_manager.operators[curOP-1].value
        #to get keyboard input change when same operator
        #check first if attribute value exists wie hasattr(obj, "atrr Name")
    if curOP == 0:
        lastOP = curOP
    if curOP>lastOP:
        lastOP = curOP
        if bpy.context.window_manager.operators[curOP-1].name == "Translate" and not bpy.context.object.mode == "EDIT":
            createReferences(scene)
            print("Scene updated")
        else:
            for o in scene.objects:
                if o.is_updated:
                    updated_objects.append(o)
            if(len(updated_objects) > 0):
                for o in updated_objects:
                    print(o, " updated")
                    createObjectRef(scene, o)

def onSave(scene):
    createReferences(bpy.context.scene)
    print("Updated on Save")
