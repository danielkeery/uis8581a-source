import sys

path = sys.argv[1]
with open(path, 'r') as f:
    c = f.read()

# Add host suspend/resume declarations after the gadget inline functions
old = 'static inline void dwc3_gadget_process_pending_events(struct dwc3 *dwc)\n{\n}\n#endif /* !IS_ENABLED(CONFIG_USB_DWC3_HOST) */'
new = 'static inline void dwc3_gadget_process_pending_events(struct dwc3 *dwc)\n{\n}\n\nint dwc3_host_suspend(struct dwc3 *dwc);\nint dwc3_host_resume(struct dwc3 *dwc);\n#endif /* !IS_ENABLED(CONFIG_USB_DWC3_HOST) */'

if old in c:
    c = c.replace(old, new)
    with open(path, 'w') as f:
        f.write(c)
    print("Patched successfully")
else:
    print("Pattern not found")
    sys.exit(1)