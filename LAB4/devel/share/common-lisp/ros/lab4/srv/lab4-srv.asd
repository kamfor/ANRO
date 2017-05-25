
(cl:in-package :asdf)

(defsystem "lab4-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "jint_control_srv" :depends-on ("_package_jint_control_srv"))
    (:file "_package_jint_control_srv" :depends-on ("_package"))
  ))