#include <stdio.h>
#include <stdlib.h>
#include "ufrn_al5d.h"
#include <Python.h>

static PyObject* py_configurar_porta(PyObject* self, PyObject* args)
{
        int command_arg;
        PyArg_ParseTuple(args, "i", &command_arg);
        int output = configurar_porta(command_arg);
        return Py_BuildValue("i", output);
}

static PyObject* py_abrir_porta(PyObject* self, PyObject* args)
{
        int output = abrir_porta();
        return Py_BuildValue("i", output);
}

static PyObject* py_enviar_comando(PyObject* self, PyObject* args)
{
        char *command_arg1;
        int command_arg2;
        PyArg_ParseTuple(args, "si", &command_arg1,&command_arg2);
        int output = enviar_comando(command_arg1,command_arg2);
        return Py_BuildValue("i", output);
}

static PyObject* py_trava(PyObject* self, PyObject* args)
{
        unsigned int command_arg1, command_arg2;
        PyArg_ParseTuple(args, "II", &command_arg1, &command_arg2);
        unsigned int output = trava(command_arg1,command_arg2);
        return Py_BuildValue("I", output);
}

static PyObject* py_fechar_porta(PyObject* self, PyObject* args)
{
        int command_arg1;
        PyArg_ParseTuple(args, "i", &command_arg1);
        fechar_porta(command_arg1);
        Py_RETURN_NONE;
}

static PyObject* py_ufrn_header(PyObject* self, PyObject* args)
{
        ufrn_header();
        Py_RETURN_NONE;
}

// Bind Python function names to our C functions
static PyMethodDef armdriver_methods[] = {
        {"configurar_porta", py_configurar_porta, METH_VARARGS},
        {"abrir_porta", py_abrir_porta, METH_VARARGS},
        {"enviar_comando", py_enviar_comando, METH_VARARGS},
        {"trava", py_trava, METH_VARARGS},
        {"fechar_porta", py_fechar_porta, METH_VARARGS},
        {"ufrn_header", py_ufrn_header, METH_VARARGS},
        {NULL, NULL}
};

//Python calls this to let us initialize our module
PyMODINIT_FUNC
initarmdriver(void)
{
        (void) Py_InitModule("armdriver", armdriver_methods);
}
