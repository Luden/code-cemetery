// AStyleInterface.cs

using System;
using System.Runtime.InteropServices;
using System.ComponentModel;
using System.Xml.Serialization;
using System.IO;
using System.Reflection;

/// AStyleInterface contains methods to call the Artistic Style formatter.
public class AStyleInterface
{   // Disable warnings for 'Missing XML comment for publicly visible type or member'
#pragma warning disable 1591

    // bracketStyle valid bracket styles
    public enum Style
    {
        STYLE_NONE       = 0,
        STYLE_ALLMAN     = 1,
        STYLE_JAVA       = 2,
        STYLE_KandR      = 3,
        STYLE_STROUSTRUP = 4,
        STYLE_WHITESMITH = 5,
        STYLE_BANNER     = 6,
        STYLE_GNU        = 7,
        STYLE_LINUX      = 8,
        STYLE_HORSTMANN  = 9,
        STYLE_1TBS       = 10,
        STYLE_PICO       = 11,
        STYLE_LISP       = 12
    };

    // indentType valid indent types
    public enum Indent
    {
        INDENT_SPACES = 0,
        INDENT_TABS   = 1,
        INDENT_FTABS  = 2
    };

    // alignPointers valid pointer alignments

    public enum Align
    {
        ALIGN_NONE = 0,
        ALIGN_TYPE = 1,
        ALIGN_MIDDLE = 2,
        ALIGN_NAME = 3
    };

    // minConditionalOption valid options
    public enum Mincond
    {
        MINCOND_ZERO = 0,
        MINCOND_ONE = 1,
        MINCOND_TWO = 2,
        MINCOND_ONEHALF = 3
    };

    // fileMode valid file modes

    public enum AstyleFilemode
    {
        CPP = 0,
        JAVA = 1,
        SHARP = 2
    };

    // Restore warnings for 'Missing XML comment for publicly visible type or member'
#pragma warning restore 1591

    // option variable names are ALMOST the same as Artistic Style
    // the initial value is the default value in Artistic Style
    // comments are the command line option used to set the variable

    [Browsable(false)]
    public bool working { get; set; }

    // bracket style option
    [DisplayName("Bracket style")]
    [Description("")]
    public Style bracketStyle { get; set; }      // --style=?

    // tabs/spaces options
    [DisplayName("Indent length")]
    [Description("")]
    public int  indentLength { get; set; }                  // --indent=?, --indent=force-tab=#

    [DisplayName("Indent type")]
    [Description("")]
    public Indent  indentType { get; set; }      // --indent=?, --indent=force-tab=#

    // indentation options
    [DisplayName("Class indent")]
    [Description("")]
    public bool classIndent { get; set; }      // --indent-classes
    [DisplayName("Switch indent")]
    [Description("")]
    public bool switchIndent { get; set; }      // --indent-switches
    [DisplayName("Case indent")]
    [Description("")]
    public bool caseIndent { get; set; }      // --indent-cases
    [DisplayName("Namespace indent")]
    [Description("")]
    public bool namespaceIndent { get; set; }      // --indent-namespaces
    [DisplayName("Label indent")]
    [Description("")]
    public bool labelIndent { get; set; }      // --indent-labels
    [DisplayName("Preprocessor indent")]
    [Description("")]
    public bool preprocessorIndent { get; set; }      // --indent-preprocessor
    [DisplayName("Col1 comment indent")]
    [Description("")]
    public bool col1CommentIndent { get; set; }      // --indent-col1-comments
    [DisplayName("Max in statement indent")]
    [Description("")]
    public int maxInStatementIndent { get; set; }         // --max-instatement-indent=#
    [DisplayName("Min conditional option")]
    [Description("")]
    public Mincond minConditionalOption { get; set; }// --min-conditional-indent=#

    // padding options
    [DisplayName("Break header blocks")]
    [Description("")]
    public bool breakHeaderBlocks { get; set; }      // --break-blocks, --break-blocks=all
    [DisplayName("Break closing blocks")]
    [Description("")]
    public bool breakClosingBlocks { get; set; }      // --break-blocks=all
    [DisplayName("Pad operators")]
    [Description("")]
    public bool padOperators { get; set; }      // --pad-oper
    [DisplayName("Pad parens outside")]
    [Description("")]
    public bool padParensOutside { get; set; }      // --pad-paren, --pad-paren-out
    [DisplayName("Pad parens inside")]
    [Description("")]
    public bool padParensInside { get; set; }      // --pad-paren, --pad-paren-in
    [DisplayName("Pad headers")]
    [Description("")]
    public bool padHeaders { get; set; }      // --pad-header
    [DisplayName("Unpad parens")]
    [Description("")]
    public bool unpadParens { get; set; }      // --unpad-paren
    [DisplayName("Delete empty lines")]
    [Description("")]
    public bool deleteEmptyLines { get; set; }      // --delete-empty-lines
    [DisplayName("Fill empty lines")]
    [Description("")]
    public bool fillEmptyLines { get; set; }     // --fill-empty-lines

    // formatting options
    [DisplayName("Break close brackets")]
    [Description("")]
    public bool breakCloseBrackets { get; set; }      // --break-closing-brackets
    [DisplayName("Break else ifs")]
    [Description("")]
    public bool breakElseIfs { get; set; }      // --break-elseifs
    [DisplayName("Add brackets")]
    [Description("")]
    public bool addBrackets { get; set; }      // --add-brackets
    [DisplayName("Add one line brackets")]
    [Description("")]
    public bool addOneLineBrackets { get; set; }      // --add-one-line-brackets
    [DisplayName("Break one line statements")]
    [Description("")]
    public bool breakOneLineStmts { get; set; }       // --keep-one-line-statements
    [DisplayName("Break one line blocks")]
    [Description("")]
    public bool breakOneLineBlocks { get; set; }       // --keep-one-line-blocks
    [DisplayName("Convert tabs")]
    [Description("")]
    public bool convertTabs { get; set; }      // --convert-tabs
    [DisplayName("Align pointers")]
    [Description("")]
    public Align alignPointers { get; set; } // align-pointer= none, type, middle, name

    // file mode option
    [DisplayName("File mode")]
    [Description("")]
    public AstyleFilemode fileMode { get; set; }        // --mode=?

    // default values for integer variables, saved by constructor
    [Browsable(false)]
    public int    defaultIndentLength;             // default indentLength
    [Browsable(false)]
    public int    defaultMaxInStatementIndent;     // default maxInStatementIndent
    [Browsable(false)]
    public Mincond    defaultMinConditionalOption;     // default minConditionalOption

    /// Constructor
    public AStyleInterface()
    {   // Declare callback functions
        AStyleMemAlloc = new AStyleMemAllocDelgate(OnAStyleMemAlloc);
        AStyleError = new AStyleErrorDelgate(OnAStyleError);
        // save integer default values
        defaultIndentLength         = indentLength;
        defaultMaxInStatementIndent = maxInStatementIndent;
        defaultMinConditionalOption = minConditionalOption;
    }

    /// Display error messages for the class.
    /// This method should be changed to display messages in a manner consistent
    /// with the rest of the user program (e.g. a message box).
    private void DisplayErrorMessage(String errorMessage)
    {   Console.WriteLine(errorMessage);
    }

    /// Build a string of options from the current option variables.
    /// An option is generated only if the current value is different
    /// than the default value.
    /// If an option variable is invalid, invalid text is sent to
    /// Artistic Style so the private ErrorHandler method will be called.
    public String GetOptions()
    {   String options = null;             // options to Artistic Style
        String separator = "\n";           // can be new-line, tab, space, or comma

        if (bracketStyle != Style.STYLE_NONE)
        {
            if (bracketStyle == Style.STYLE_ALLMAN)
                options += "style=allman";
            else if (bracketStyle == Style.STYLE_JAVA)
                options += "style=java";
            else if (bracketStyle == Style.STYLE_KandR)
                options += "style=k&r";
            else if (bracketStyle == Style.STYLE_STROUSTRUP)
                options += "style=stroustrup";
            else if (bracketStyle == Style.STYLE_WHITESMITH)
                options += "style=whitesmith";
            else if (bracketStyle == Style.STYLE_BANNER)
                options += "style=banner";
            else if (bracketStyle == Style.STYLE_GNU)
                options += "style=gnu";
            else if (bracketStyle == Style.STYLE_LINUX)
                options += "style=linux";
            else if (bracketStyle == Style.STYLE_HORSTMANN)
                options += "style=horstmann";
            else if (bracketStyle == Style.STYLE_1TBS)
                options += "style=1tbs";
            else if (bracketStyle == Style.STYLE_PICO)
                options += "style=pico";
            else if (bracketStyle == Style.STYLE_LISP)
                options += "style=lisp";
            else
                options += "bracketStyle="      // force an error message
                           + bracketStyle;
            options += separator;
        }
        // begin indent check
        if (indentType == Indent.INDENT_SPACES)           // space is the default
        {   if (indentLength != defaultIndentLength)
            {   options += "indent=spaces=" + indentLength;
                options += separator;
            }
        }
        else if (indentType == Indent.INDENT_TABS)        // tab is not the default
        {   // check conditions to use default tab setting
            if (indentLength == defaultIndentLength)
                options += "indent=tab";
            else
                options += "indent=tab=" + indentLength;
            options += separator;
        }
        else if (indentType == Indent.INDENT_FTABS)
        {   options += "indent=force-tab=" + indentLength;
            options += separator;
        }
        else
        {   options += "indentType="               // force an error message
                       + indentType;
            options += separator;
        }
        // end indent check
        if (classIndent)
        {   options += "indent-classes";
            options += separator;
        }
        if (switchIndent)
        {   options += "indent-switches";
            options += separator;
        }
        if (caseIndent)
        {   options += "indent-cases";
            options += separator;
        }
        if (namespaceIndent)
        {   options += "indent-namespaces";
            options += separator;
        }
        if (labelIndent)
        {   options += "indent-labels";
            options += separator;
        }
        if (preprocessorIndent)
        {   options += "indent-preprocessor";
            options += separator;
        }
        if (col1CommentIndent)
        {   options += "indent-col1-comments";
            options += separator;
        }
        if (maxInStatementIndent != defaultMaxInStatementIndent)
        {   options += "max-instatement-indent="
                       + maxInStatementIndent;
            options += separator;
        }
        if (minConditionalOption != defaultMinConditionalOption)
        {   options += "min-conditional-indent="
                       + minConditionalOption;
            options += separator;
        }
        // begin break-blocks check
        if (breakClosingBlocks)
        {   options += "break-blocks=all";
            options += separator;
        }
        else if (breakHeaderBlocks)
        {   options += "break-blocks";
            options += separator;
        }
        // end break-blocks check
        if (padOperators)
        {   options += "pad-oper";
            options += separator;
        }
        // begin pad parens check
        if (padParensOutside && padParensInside)
        {   options += "pad-paren";
            options += separator;
        }
        else if (padParensOutside)
        {   options += "pad-paren-out";
            options += separator;
        }
        else if (padParensInside)
        {   options += "pad-paren-in";
            options += separator;
        }
        // end pad parens check
        if (padHeaders)
        {   options += "pad-header";
            options += separator;
        }
        if (unpadParens)
        {   options += "unpad-paren";
            options += separator;
        }
        if (deleteEmptyLines)
        {   options += "delete-empty-lines";
            options += separator;
        }
        if (fillEmptyLines)
        {   options += "fill-empty-lines";
            options += separator;
        }
        if (breakCloseBrackets)
        {   options += "break-closing-brackets";
            options += separator;
        }
        if (breakElseIfs)
        {   options += "break-elseifs";
            options += separator;
        }
        if (addBrackets)
        {   options += "add-brackets";
            options += separator;
        }
        if (addOneLineBrackets)
        {   options += "add-one-line-brackets";
            options += separator;
        }
        if (! breakOneLineStmts)               // default = true
        {   options += "keep-one-line-statements ";
            options += separator;
        }
        if (! breakOneLineBlocks)              // default = true
        {   options += "keep-one-line-blocks";
            options += separator;
        }
        if (convertTabs)
        {   options += "convert-tabs";
            options += separator;
        }
        // begin align pointers check
        if (alignPointers == Align.ALIGN_TYPE)
        {   options += "align-pointer=type";
            options += separator;
        }
        else if (alignPointers == Align.ALIGN_MIDDLE)
        {   options += "align-pointer=middle";
            options += separator;
        }
        else if (alignPointers == Align.ALIGN_NAME)
        {   options += "align-pointer=name";
            options += separator;
        }
        // end align pointers check
        // add the file mode, default is C++
        if (fileMode == AstyleFilemode.CPP)
        {   if (options.Length > 0)            // delete the last separator
                options.TrimEnd('\n');
        }
        else if (fileMode == AstyleFilemode.JAVA)
            options += "mode=java";
        else if (fileMode == AstyleFilemode.SHARP)
            options += "mode=cs";
        else
            options += "fileMode=" + fileMode; // force an error message

        return options;
    }

    /// Set the fileMode variable from the input file extension.
    public void SetFileMode(String fileName)
    {
        fileMode = AstyleFilemode.CPP;
        if (fileName.EndsWith(".java"))
            fileMode = AstyleFilemode.JAVA;
        else if (fileName.EndsWith(".cs"))
            fileMode = AstyleFilemode.SHARP;
    }

    public void SaveSettings()
    {
        try
        {
            String path = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            var serializer = new XmlSerializer(typeof(AStyleInterface));
            using (var writer = new StreamWriter(path + "\\Settings.xml"))
            {
                serializer.Serialize(writer, this);
            }
        }
        catch (System.Exception ex)
        {
        	
        }
    }

    public static void LoadSettings(ref AStyleInterface ai)
    {
        try
        {
            String path = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            var serializer = new XmlSerializer(typeof(AStyleInterface));
            using (var reader = new StreamReader(path + "\\Settings.xml"))
            {
                ai = (AStyleInterface)serializer.Deserialize(reader);
            }
        }
        catch (System.Exception ex)
        {
        }
    }

    public void LoadDefaults()
    {
        working = true;
        
        // bracket Style options
        bracketStyle = Style.STYLE_NONE;

        // tabs / spaces options
        indentType = Indent.INDENT_TABS;
        alignPointers = Align.ALIGN_NONE;
        minConditionalOption = Mincond.MINCOND_TWO;
        fileMode = AstyleFilemode.CPP;
        indentLength = 4;

        // indentation options
        classIndent        = false;
        switchIndent = false;
        caseIndent = false;
        namespaceIndent = false;
        labelIndent = false;
        preprocessorIndent = false;
        col1CommentIndent = false;
        maxInStatementIndent = 40;
        

        // padding options
        breakHeaderBlocks  = false;
        breakClosingBlocks = false;
        padOperators = true;
        padParensOutside   = false;
        padParensInside    = false;
        padHeaders         = false;
        unpadParens        = true;
        deleteEmptyLines   = false;
        fillEmptyLines     = false;

        // formatting options
        breakCloseBrackets = false;
        breakElseIfs       = false;
        addBrackets        = false;
        addOneLineBrackets = false;
        breakOneLineStmts  = false;
        breakOneLineBlocks = false;
        convertTabs        = false;
        
    }

    // functions to call Artistic Style ---------------------------------------------------

    // Cannot use String as a return value because Mono runtime will attempt to
    // free the returned pointer resulting in a runtime crash.
    [DllImport("astyle", CallingConvention = CallingConvention.StdCall)]
    private static extern IntPtr AStyleMain
    (
        [MarshalAs(UnmanagedType.LPStr)] String sIn,
        [MarshalAs(UnmanagedType.LPStr)] String sOptions,
        AStyleErrorDelgate errorFunc,
        AStyleMemAllocDelgate memAllocFunc
    );

    /// AStyleMain callbacks
    private delegate IntPtr AStyleMemAllocDelgate(int size);
    private delegate void AStyleErrorDelgate
    (
        int errorNum,
        [MarshalAs(UnmanagedType.LPStr)] String error
    );

    /// AStyleMain Delegates
    private AStyleMemAllocDelgate AStyleMemAlloc;
    private AStyleErrorDelgate AStyleError;

    /// Call the AStyleMain function in Artistic Style.
    /// An empty string is returned on error.
    public String FormatSource(String textIn)
    {   String options = GetOptions();
//        DisplayErrorMessage("--------------------\n"
//                           + options + "\n"
//                           + "--------------------" );
        // Return the allocated string
        // Memory space is allocated by OnAStyleMemAlloc, a callback function from AStyle
        String sTextOut = String.Empty;
        try
        {   IntPtr pText = AStyleMain(textIn, options, AStyleError, AStyleMemAlloc);
            if (pText != IntPtr.Zero)
            {   sTextOut = Marshal.PtrToStringAnsi(pText);
                Marshal.FreeHGlobal(pText);
            }
        }
        catch (BadImageFormatException e)
        {   DisplayErrorMessage(e.ToString());
            DisplayErrorMessage("You may be mixing 32 and 64 bit code!");
        }
        catch (Exception e)
        {   DisplayErrorMessage(e.ToString());
        }
        return sTextOut;
    }

    /// Set fileMode and call the AStyleMain function in Artistic Style.
    public String FormatSource(String textIn, String fileName)
    {   SetFileMode(fileName);
        String textOut = FormatSource(textIn);
        return textOut;
    }

    /// Set fileMode and call the AStyleMain function in Artistic Style.
    public String FormatSource(String textIn, AstyleFilemode fileModeArg)
    {   // set file mode before formatting source
        fileMode = fileModeArg;
        String textOut = FormatSource(textIn);
        return textOut;
    }

    /// Allocate the memory for the Artistic Style return string.
    private IntPtr OnAStyleMemAlloc(int size)
    {   return Marshal.AllocHGlobal(size);
    }

    /// Display errors from Artistic Style .
    private void OnAStyleError(int errorNumber, String errorMessage)
    {   DisplayErrorMessage("astyle error " + errorNumber + " - " + errorMessage);
    }

}   // class AStyleInterface
