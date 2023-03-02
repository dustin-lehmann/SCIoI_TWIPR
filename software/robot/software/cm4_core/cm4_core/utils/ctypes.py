import ctypes


def struct_to_dict(struct: ctypes.Structure):
    return dict((f, getattr(struct, f)) for f, _ in struct._fields_)